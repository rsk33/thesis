/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Analysis.cpp                                                                                    */
/* File Type:           Source-File                                                                                     */
/* Creation Date:       01.08.2017                                                                                      */
/* Version:             1.0                                                                                             */
/* Author:              Roman Skybinskyi <r.skybinskyi@yahoo.com>                                                       */
/* Supervisor:          Prof. Dr.-Ing. Carsten Braun <c.braun@fh-aachen.de>                                             */
/*                                                                                                                      */
/*----------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                      */
/* Contact Details:     University of Applied Sciences                                                                  */
/*                      Faculty 6 - Aerospace Engineering                                                               */
/*                      Aircraft Engineering                                                                            */
/*                      Hohenstaufenallee 6                                                                             */
/*                      52064 Aachen (Germany)                                                                          */
/*                                                                                                                      */
/*----------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                      */
/* Disclaimer:          The author assumes no responsibility in any form for the use of this software, errors herein,   */
/*                      or any imaginable damages resulting from its usage. Always crosscheck the results.              */
/*----------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                      */
/*! Copyright (c) 2017 FH Aachen                                                                                        */
/*                                                                                                                      */
/************************************************************************************************************************/

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>

#include "Analysis.h"
#include "../vehicle/Aircraft.h"
#include "../vehicle/Component.h"
#include "../vehicle/Geom.h"
#include "../std_lib_facilities.h"
#include "../control/Settings.h"
#include "../vsp/Process.h"
#include "../vsp/Comp_geom.h"
#include "../vsp/Script.h"
#include "../vsp/Polar.h"
#include "../vsp/Stab.h"
#include "../vsp/Lod.h"
#include "../Atmosphere.h"
#include "Horiz_stab_sizing.h"

using namespace std;


namespace Calculation {

// Analysis constructor constructs instance of analysis with settings, requirements and initial sizing objects
// Settings object is used to configure analysis
Analysis::Analysis(const Control::Settings& settings, const Requirements& requirements,
                    const Initial_sizing& initial_sizing)
: m_settings{settings}, m_results{settings,requirements,initial_sizing} {}

// interface functions for wet area calculation.
// function determines which method to use and calls function for the specific method.
// calculated value is stored in aircraft object
void Analysis::wet_area(Vehicle::Aircraft& aircraft) const
{
    if( m_settings.wet_area == Method::vsp){

        cout << "Wet area is analyzed by " << method_to_string(Method::vsp) << '\n';

        wet_area_vsp(aircraft); // call function which calculates wet area using OpenVSP analysis
    }
    else
        error("wet area analysis method undefined");
}

// interface functions mass calculation.
// calculated value is stored in aircraft object
void Analysis::mass(Vehicle::Aircraft& aircraft) const
{
    // mass calculation requires wet area values to be calculated first
    wet_area(aircraft);

    // operating empty mass calculation requires initial mass assumption
    // initially value specified by initial sizing is used
    // mass is calculated iteratively until difference between previous and subsequent iterations
    // is smaller than 1%
    double old_mass;
    double diff{1};
    while(diff > 0.01){

        old_mass = aircraft.mass_operating_empty();

        // determine which method to be used
        if( m_settings.mass == Method::torenbeek_2){

            cout << "Mass is analyzed by " << method_to_string(Method::torenbeek_2) << '\n';

            // calculate masses of individual components
            torenbeek_mass_second_class_fuselage(aircraft);
            torenbeek_mass_second_class_main_wing(aircraft);
            torenbeek_mass_second_class_horiz_tail(aircraft);
            torenbeek_mass_second_class_vert_tail(aircraft);

        }
        else
            error("mass analysis method undefined");

        // calculate empty operating mass
        // calculate sum of components mass
        double total = aircraft.fuselage().mass() +
                        aircraft.main_wing().mass() +
                        aircraft.horiz_tail().mass() +
                        aircraft.vert_tail().mass();

        // add weight groups specified by initial sizing file
        for(auto x : aircraft.weight_groups())
            total += x.mass();

        aircraft.set_mass_operating_empty(total);

        // calculated relative difference with previous step
        diff = abs((total - old_mass)/total);
    }
}

// interface function - zero lift drag calculation.
// calculated value is stored in aircraft object
void Analysis::zero_lift_drag(Vehicle::Aircraft& aircraft) const
{
    // determine which method to be used
    if( m_settings.zero_lift_drag == Method::drag_build_up_raymer){

        // calculate fuselage zero lift drag and store it in fuselage object
        zero_lift_drag_raymer(aircraft.fuselage(),aircraft.cruise_alt(),
                             aircraft.cruise_mach(),aircraft.ref_area());

        // calculate wing zero lift drag and store it in wing object
        zero_lift_drag_raymer(aircraft.main_wing(),aircraft.cruise_alt(),
                             aircraft.cruise_mach(),aircraft.ref_area());

        // calculate horizontal tail zero lift drag and store it in horizontal tail object
        zero_lift_drag_raymer(aircraft.horiz_tail(),aircraft.cruise_alt(),
                             aircraft.cruise_mach(),aircraft.ref_area());

        // calculate vertical tail zero lift drag and store it in vertical tail object
        zero_lift_drag_raymer(aircraft.vert_tail(),aircraft.cruise_alt(),
                             aircraft.cruise_mach(),aircraft.ref_area());
    }
    else
        error("Zero lift drag analysis method undefined");

    // calculate total zero lift drag and account for a propulsion integration
    double total = ( aircraft.fuselage().zero_lift_drag() +
                    aircraft.main_wing().zero_lift_drag() +
                    aircraft.vert_tail().zero_lift_drag() +
                    aircraft.horiz_tail().zero_lift_drag() ) * 1.1;

    // update aircraft total zero lift drag value
    aircraft.set_zero_lift_drag(total);
}

// interface function - lift induced drag calculation.
// calculated value is stored in aircraft object
void Analysis::lift_induced_drag(Vehicle::Aircraft& aircraft) const
{
    // calculates Oswald's factor per Douglas method
    if( m_settings.lift_induced_drag == Method::douglas){

        lift_induced_drag_douglas(aircraft);
    }
    // calculates Oswald's number using VSPAero VLM method
    else if(m_settings.lift_induced_drag == Method::vsp_aero_vlm){

        lift_induced_drag_vsp_aero_vlm(aircraft);
    }
    // calculates Oswald's number using VSPAero Panel method
    else if(m_settings.lift_induced_drag == Method::vsp_aero_panel){

        lift_induced_drag_vsp_aero_panel(aircraft);
    }
    else
        error("Lift induced drag analysis method undefined");
}

// function analyses influence of the variable specified by the settings file on the aircraft range
// output vsp model is updated with optimal variable value
void Analysis::design_to_range(Vehicle::Aircraft& aircraft)
{
    // create the vsp process
    Vsp::Process proc{m_settings.vsp_dir};

    // define variable by the min, max and delta values
    double variable = m_settings.variable.min_value();
    double max_value = m_settings.variable.max_value();
    double delta = m_settings.variable.delta();

    // initialize key - value pairs for scripts creation
    map<string,string> key_value_set;
    key_value_set["\\$file_name"] = m_settings.file_name(Control::File_type::vsp_new);
    key_value_set["\\$out_file_name"] = m_settings.file_name(Control::File_type::main_wing_and_ht_only);
    key_value_set["\\$comp_name"] = m_settings.variable.geom_name();
    key_value_set["\\$group_name"] = m_settings.variable.group_name();
    key_value_set["\\$param_name"] = m_settings.variable.param_name();
    key_value_set["\\$value"] = to_string(variable);

    // vector declaration to store variable - range pairs
    vector<pair<double,double>> results;

    int iteration_count = 1;

    // loop through all variable values
    while(variable <= max_value){

        cout << "// Iteration " << iteration_count << " //\n";
        cout << m_settings.variable.full_name() << '\n';
        cout << "Variable = " << variable << '\n';

        // reassign variable value for the current iteration
        key_value_set["\\$value"] = to_string(variable);

        // create vsp script out of the template
        Vsp::Script modify_model{Vsp::Script::modify_geom_param,key_value_set};

        // execute the script
        proc.execute(modify_model);

        // read the new vsp model geometry
        Vehicle::read_geom(aircraft, m_settings.file_name(Control::File_type::vsp_new));

        mass(aircraft);                 // mass calculation
        zero_lift_drag(aircraft);       // zero lift drag calculation
        lift_induced_drag(aircraft);    // lift induced drag calculation
        // results are stored in aircraft object

        // add polar to results manager
        m_results.add_polar(aircraft, variable);

        // add variable - range pair to results manager
        m_results.add_pair(variable, aircraft.range());

        // instance of report, used for xml output of aircraft parameters per each iteration
        Range_des_report report;

        // assign parameter values
        report.lift_to_drag_cruise = aircraft.lift_to_drag_cruise();
        report.mass_max_take_off = aircraft.mass_max_take_off();
        report.mass_oper_empty = aircraft.mass_operating_empty();
        report.mass_fus = aircraft.fuselage().mass();
        report.mass_wing = aircraft.main_wing().mass();
        report.mass_horiz_tail = aircraft.horiz_tail().mass();
        report.mass_vert_tail = aircraft.vert_tail().mass();

        // summarize systems masses
        double tot_mass_sys{};
        for( auto x : aircraft.weight_groups()){
            tot_mass_sys += x.mass();
        }

        // assign rest parameters vales
        report.mass_sys = tot_mass_sys;
        report.mass_fuel = aircraft.mass_fuel();
        report.mass_payload = aircraft.mass_payload();

        // save report with aircraft performances
        m_results.add_range_des_report(report);

        // increment parameter
        variable += delta;
        // increment iteration count
        ++iteration_count;

        cout << '\n';
    }

    // show to console "design with respect to range" results
    m_results.show_des_study();

    // save to xml file "design with respect to range" results
    //m_results.outp_des_study();

    // save polar results to xml file
    m_results.outp_polar();

    // update model with optimal value
    double var{};
    double val{};

    // find optimal variable value and update aircraft vsp file with that value
    if(m_results.optimum(var,val)){

        key_value_set["\\$value"] = to_string(var);

        // create script out of the template
        Vsp::Script modify_model{Vsp::Script::modify_geom_param,key_value_set};

        // modify model with optimal variable value
        proc.execute(modify_model);

        // read aircraft geometry
        Vehicle::read_geom(aircraft, m_settings.file_name(Control::File_type::vsp_new));

        // calculate mass and drag
        mass(aircraft);
        zero_lift_drag(aircraft);
        lift_induced_drag(aircraft);
    }

}

// horizontal stabilizer sizing function
// output aircraft vsp model is updated with optimal value of horizontal stabilizer area
void Analysis::horiz_stab_sizing(Vehicle::Aircraft& aircraft)
{
    if(m_settings.trim == Method::vsp &&
        m_settings.static_stability == Method::vsp){

        if(!vsp_horiz_stab_sizing(aircraft))
                cout << "Horizontal Stabilizer Sizing Failed\n";
    }
    else
        cout << "Horizontal Stabilizer Sizing not defined\n";

}

// wet area calculation
void Analysis::wet_area_vsp(Vehicle::Aircraft& aircraft) const
{
    // create vsp process
    Vsp::Process proc{m_settings.vsp_dir};

    // initialize key - value pair for the script modification
    map<string,string> key_value_set;
    key_value_set["\\$file_name"] = m_settings.file_name(Control::File_type::vsp_new);

    // create compute geometry script out of the template
    Vsp::Script comp_geom{Vsp::Script::compute_comp_geom,key_value_set};

    // execute script
    proc.execute(comp_geom);

    // open csv file with results for reading
    ifstream ist {m_settings.file_name(Control::File_type::comp_geom_csv)};
    if(!ist) error("could not open", m_settings.file_name(Control::File_type::comp_geom_csv));

    // declare vector to store results
    vector<Vsp::Comp_geom> comp_geoms;

    // fill the vector with results read from the file
    fill_vector(ist,comp_geoms);

    // show the results to the console
    for(auto x : comp_geoms)
        cout << x << '\n';
    cout << '\n';

    // read wet areas and assign them to the aircraft object

    // assign obtained fuselage wet area values to the aircraft object (in-memory representation)
    for(int i {}; i<int(comp_geoms.size()); ++i){

        // use fuselage name for the wet area entry identification
        string fus_id = aircraft.fuselage().id();

        // if the fuselage wet area found assign it to the aircraft object
        if(comp_geoms[i].name.compare(0,fus_id.size(),fus_id) == 0){
            aircraft.fuselage().set_wet_area(comp_geoms[i].theor_area);
        }
    }

    for(int i {}; i<int(comp_geoms.size()); ++i){

        string wing_id = aircraft.main_wing().id();

        if(comp_geoms[i].name.compare(0,wing_id.size(),wing_id) == 0){
            aircraft.main_wing().set_wet_area(comp_geoms[i].theor_area);
        }
    }

    for(int i {}; i<int(comp_geoms.size()); ++i){

        string horiz_tail_id = aircraft.horiz_tail().id();

        if(comp_geoms[i].name.compare(0,horiz_tail_id.size(),horiz_tail_id) == 0){
            aircraft.horiz_tail().set_wet_area(comp_geoms[i].theor_area);
        }
    }

    for(int i {}; i<int(comp_geoms.size()); ++i){

        string vert_tail_id = aircraft.vert_tail().id();

        if(comp_geoms[i].name.compare(0,vert_tail_id.size(),vert_tail_id) == 0){
            aircraft.vert_tail().set_wet_area(comp_geoms[i].theor_area);
        }
    }
}

// calculate the fuselage mass per Torenbeek II Class mass estimation method
// and assign it to the aircraft object
void Analysis::torenbeek_mass_second_class_fuselage(Vehicle::Aircraft& aircraft) const
{
    // coefficients
    double constant = 0.23; // units

    double mass_penalty_press = 1.08;   // pressurized fuselage

    double mass_penalty_rear_eng = 1.04;    // rear located engines

    double cruise_speed = aircraft.cruise_mach() *
                            Atmosphere::speed_of_sound(aircraft.cruise_alt());

    double design_speed = cruise_speed / 0.8;     // design dive speed

    // distance between the wing and horizontal stabilizer aerodynamic centers
    double horiz_tail_lever = aircraft.horiz_tail_lever();

    double width = aircraft.fuselage().diam();
    double height = aircraft.fuselage().diam();

    double fus_wet_area = aircraft.fuselage().wet_area();

    // fuselage empty weight
    double mass = constant * mass_penalty_press * mass_penalty_rear_eng *
                    pow ( design_speed * horiz_tail_lever /
                    ( width + height ) , 0.5 ) * pow ( fus_wet_area, 1.2 );

    // assign obtained value to the aircraft object
    aircraft.fuselage().set_mass(mass);
}

// calculate the wing mass per Torenbeek II Class mass estimation method
// and assign it to the aircraft object
void Analysis::torenbeek_mass_second_class_main_wing(Vehicle::Aircraft& aircraft) const
{
    double coef{};  // factor of proportionality

    if(aircraft.mass_max_take_off() < 5670){
        coef = 4.90 * pow( 10, -3 );   // factor of proportionality for Take-off weight < 5670 [kg]
    }
    else{
        coef = 6.67 * pow( 10, -3 );   // factor of proportionality for Take-off weight > 5670 [kg]
    }

    double ult_load_factor = aircraft.ult_load_factor();

    // structural wing span [m]
    double struct_span = aircraft.main_wing().span() /
                                cos( aircraft.main_wing().sweep(0.5) * PI / 180 );

    double ref_span = 1.905;    // reference span [m]

    double area = aircraft.main_wing().area();

    double root_thick = aircraft.main_wing().root_thick() *
                        aircraft.main_wing().root_chord();

    double gross_mass = aircraft.mass_gross();

    double spoiler_penalty = 1.02;      // spoilers and speed break penalty

    double mass = coef * pow( struct_span, 0.75 ) * ( 1 + sqrt( ref_span / struct_span ) ) *
                    pow( ult_load_factor, 0.55 ) * pow( struct_span * area /
                    ( root_thick * gross_mass ), 0.3) * spoiler_penalty * gross_mass;

    // assign obtained value to the aircraft object
    aircraft.main_wing().set_mass(mass);
}

// calculate the horizontal stabilizer mass per Torenbeek II Class mass estimation method
// and assign it to the aircraft object
void Analysis::torenbeek_mass_second_class_horiz_tail(Vehicle::Aircraft& aircraft) const
{
    double mass{};

    double area = aircraft.horiz_tail().area();

    double dive_speed = aircraft.cruise_speed() / 0.8;

    if(dive_speed < 129){  // if speed < 250 kts (light aircraft))

        double corr_factor = 0.64; // correction factor
        mass = corr_factor * pow( aircraft.ult_load_factor() * pow( area , 2 ) , 0.75 );
    }
    else{   // transport aircraft

        double scale_f; // scale effect factor

        // argument to scaling function
        double x = pow( area, 0.2 ) * dive_speed / 1000 /
                    sqrt( cos( aircraft.horiz_tail().sweep(0.25) * PI / 180 ) );

        // description of scaling factor graph (approximation)
        if(x < 0.5){ // part of the graph with constant slope

            double slope = 63.3; // slope of scaling function
            scale_f = ( x - 0.6 ) * slope + 0.6;
            if(scale_f < 10){   // lower bound
                scale_f = 10;
            }
        }
        else{   // part of the plot with constant function
            scale_f = 29;
        }

        // calculate mass
        mass = area * scale_f;
    }

    // assign the obtained mass to the aircraft object
    aircraft.horiz_tail().set_mass(mass);

}

// calculate the vertical stabilizer mass per Torenbeek II Class mass estimation method
// and assign it to the aircraft object
void Analysis::torenbeek_mass_second_class_vert_tail(Vehicle::Aircraft& aircraft) const
{
    double mass{};

    double area = aircraft.vert_tail().area();

    double dive_speed = aircraft.cruise_speed() / 0.8;

    if(dive_speed < 129){  // if speed < 250 kts (light aircraft))

        double corr_factor = 0.64; // correction factor
        mass = corr_factor * pow( aircraft.ult_load_factor() * pow( area , 2 ) , 0.75 );
    }
    else{   // transport aircraft

        double scale_f; // scale effect factor

        // argument to scaling function
        double x = pow( area, 0.2 ) * dive_speed / 1000 /
                    sqrt( cos( aircraft.vert_tail().sweep(0.25) * PI / 180 ) );

        // description of scaling factor graph (approximation)
        if(x < 0.5){ // part of the graph with constant slope

            double slope = 63.3; // slope of scaling function
            scale_f = ( x - 0.6 ) * slope + 0.6;
            if(scale_f < 10){   // lower bound
                scale_f = 10;
            }
        }
        else{   // part of the plot with constant function
            scale_f = 29;
        }

        mass = area * scale_f;
    }

    double horiz_tail_hight = abs( aircraft.horiz_tail().loc().z() - aircraft.vert_tail().loc().z() );

    double area_ratio = aircraft.horiz_tail().area() / aircraft.vert_tail().area();

    // correction factor due to t-tail, HT/VT area ratio assumed to be 1
    double t_tail_penalty = 1 + 0.15 * area_ratio * horiz_tail_hight / aircraft.vert_tail().span();

    mass *= t_tail_penalty;

    // assign obtained value to aircraft object
    aircraft.vert_tail().set_mass(mass);
}

// calculate fuselage zero lift drag per Raymer and assign obtained value to
// the fuselage object
void Analysis::zero_lift_drag_raymer(Vehicle::Fuselage& fuselage, double cruise_alt,
                                    double cruise_mach, double ref_area) const
{
    double fineness_ratio = fuselage.fineness();

    double skin_fric = skin_friction(fuselage.length(), cruise_mach, cruise_alt);

    double form_factor = 1 + 60 / pow(fineness_ratio, 3) + fineness_ratio / 400;

    const double interference = 1;  // interference factor

    double zero_drag = skin_fric * form_factor * interference *
                        fuselage.wet_area() / ref_area;

    // assign calculated value to the fuselage object
    fuselage.set_zero_lift_drag(zero_drag);
}

// calculate wing zero lift drag per Raymer and assign obtained value to
// the wing object
void Analysis::zero_lift_drag_raymer(Vehicle::Wing& wing, double cruise_alt,
                                    double cruise_mach, double ref_area) const
{
    double skin_fric = skin_friction(wing.mean_geom_chord(), cruise_mach, cruise_alt);

    double max_thick_chordwise_loc = 0.3;   // currently assumed 0.3 of chord (applicable to NACA 4 digit airfoil)

    double max_thick_sweep = wing.sweep(max_thick_chordwise_loc);

    double thickness = wing.av_thick();

    double form_factor = ( 1 + 0.6 * thickness / max_thick_chordwise_loc + 100 *
                          pow( thickness, 4 ) ) * ( 1.34 * pow( cruise_mach, 0.18 ) *
                          pow( cos( max_thick_sweep * PI / 180 ), 0.28 ) );

    const double interference = 1;  // interference factor

    double zero_drag = skin_fric * form_factor * interference *
                        wing.wet_area() / ref_area;

    wing.set_zero_lift_drag(zero_drag);
}

// Skin fraction calculation per Raymer
// function returns result as a double value
double Analysis::skin_friction(double characteristic_length, double mach, double alt) const
{
    double velocity = mach * Atmosphere::speed_of_sound(alt);

    double reynolds = velocity * characteristic_length / Atmosphere::kin_visc(alt);

    double skin_friction = 0.455 / ( pow( log10(reynolds), 2.58) *
                            pow( (1 + 0.144 * pow(mach, 2) ), 0.65 ) );

    return skin_friction;
}

// function calculates Oswald's factor per Douglas method and assigns it to the aircraft object
void Analysis::lift_induced_drag_douglas(Vehicle::Aircraft& aircraft) const
{
    double aspect_ratio = aircraft.main_wing().aspect();

    // sweep along the leading edge
    double main_wing_le_sweep = aircraft.main_wing().sweep(0);

    double parasit_corr_fact = 0.38 - main_wing_le_sweep /
                                3000 + pow(main_wing_le_sweep, 2) / 15000;

    double corr_fact_non_elipt_planf = 0.99;

    double fus_width = aircraft.fuselage().diam();

    double wing_span = aircraft.main_wing().span();

    double fus_width_to_wing_span = fus_width / wing_span;

    double zero_lift_drag = aircraft.zero_lift_drag();

    double oswalds_factor = 1 / (PI * aspect_ratio * parasit_corr_fact * zero_lift_drag +
                            1 / ((1 + 0.03 * fus_width_to_wing_span - 2 *
                            pow(fus_width_to_wing_span, 2)) * corr_fact_non_elipt_planf));

    aircraft.set_oswald(oswalds_factor);

}

// function calculates Oswald's factor using VSPAero VLM analysis
// and assigns it to the aircraft object
void Analysis::lift_induced_drag_vsp_aero_vlm(Vehicle::Aircraft& aircraft) const
{
    // crate VSP process
    Vsp::Process proc {m_settings.vsp_dir};

    // make a reduced model which consists of the wing and horizontal stabilizer only

    // initialize key - value pairs for the script creation
    map<string,string> key_value_set;
    key_value_set["\\$file_name"] = m_settings.file_name(Control::File_type::vsp_new);
    key_value_set["\\$out_file_name"] = m_settings.file_name(Control::File_type::main_wing_and_ht_only);

    // create script out of the template
    Vsp::Script vspaero_model{Vsp::Script::write_vspaero_model,key_value_set};

    // execute script
    proc.execute(vspaero_model);

    // create degenerate geometry script
    // degen geometry is created out of the reduced geometry model
    key_value_set["\\$file_name"] = m_settings.file_name(Control::File_type::main_wing_and_ht_only);

    // create degen geom script
    Vsp::Script degen_geom{Vsp::Script::compute_degen_geom,key_value_set};

    // execute script
    proc.execute(degen_geom);

    // run analysis for two angles of attack
    // to interpolate AoA for required lift coefficient

    // VSPAero setup
    double ref_area = aircraft.main_wing().area();
    double ref_span = aircraft.main_wing().span();
    double ref_chord = aircraft.main_wing().mean_geom_chord();
    double cg_x = aircraft.cg().x();
    double cg_y = aircraft.cg().y();
    double cg_z = aircraft.cg().z();
    tuple<double,double,double> cg = make_tuple(cg_x,cg_y,cg_z);    // CG position
    vector<double> mach {m_settings.vspaero_mach};
    double aoa_1 = 0;
    double aoa_2 = 10;
    vector<double> aoa {aoa_1, aoa_2};
    vector<double> beta {0};
    int wakeiter = m_settings.vspaero_wakes;
    bool symm = false;
    int threads = m_settings.vspaero_threads;
    bool stab = false;

    // create vspaero setup
    Vsp::Aero aero {ref_area, ref_span, ref_chord, cg, mach, aoa, beta, wakeiter, symm, threads, stab,
                        m_settings.file_name(Control::File_type::main_wing_and_ht_only_degen_geom_csv)};
    // run vspaero
    proc.execute(aero);

    // open polar file for read-in
    ifstream ist {m_settings.file_name(Control::File_type::main_wing_and_ht_only_vspaero_polar)};
    if(!ist) error("could not open", m_settings.file_name(Control::File_type::main_wing_and_ht_only_vspaero_polar));

    // create container of Polar data type
    vector<Vsp::Polar> vp;

    // fill container with data from the file
    fill_vector(ist,vp);

    // find the entry with AoA = 0
    auto p1 = find_if(vp.begin(),vp.end(),[](const Vsp::Polar& p){ return p.alpha==0; } );

    // assign lift coefficient value at AoA = 0
    double lift_1 = p1->lift;

    // find the entry with AoA = 10
    auto p2 = find_if(vp.begin(),vp.end(),[](const Vsp::Polar& p){ return p.alpha==10; } );

    // assign lift coefficient value at AoA = 10
    double lift_2 = p2->lift;

    double lift_cruise = aircraft.lift_coef_cruise();

    double aoa_cruise{};

    // interpolate AoA required to reach cruise lift
    aoa_cruise = ( lift_cruise - lift_1 ) * ( aoa_2 - aoa_1 ) / ( lift_2 - lift_1 ) + aoa_1;

    vector<double> aoa_cr {aoa_cruise};

    // create vspaero setup for cruise AoA analysis
    Vsp::Aero aero_cruise {ref_area, ref_span, ref_chord, cg, mach, aoa_cr, beta, wakeiter, symm, threads, stab,
                            m_settings.file_name(Control::File_type::main_wing_and_ht_only_degen_geom_csv)};

    // run vspaero analysis
    proc.execute(aero_cruise);

    // open vspaero polar file for read-in
    ifstream ist_c {m_settings.file_name(Control::File_type::main_wing_and_ht_only_vspaero_polar)};
    if(!ist_c) error("could not open", m_settings.file_name(Control::File_type::main_wing_and_ht_only_vspaero_polar));

    vector<Vsp::Polar> vp_cruise;

    fill_vector(ist_c,vp_cruise);

    // assign Oswald's factor
    if(vp_cruise.size()==1){

        aircraft.set_oswald(vp_cruise[0].oswald);
    }
}

// function calculates Oswald's factor using VSPAero Panel analysis
// and assigns it to the aircraft object
void Analysis::lift_induced_drag_vsp_aero_panel(Vehicle::Aircraft& aircraft) const
{
    // create vsp process
    Vsp::Process proc {m_settings.vsp_dir};

    // initialize key - value pairs for the *.tri file exporting script
    map<string,string> key_value_set;
    key_value_set["\\$file_name"] = m_settings.file_name(Control::File_type::vsp_new);
    key_value_set["\\$out_file_name"] = m_settings.file_name(Control::File_type::tri);

    // create script out of the script template
    Vsp::Script export_tri{Vsp::Script::export_tri_file,key_value_set};

    // execute script
    proc.execute(export_tri);

    // run analysis for two angles of attack
    // to interpolate AoA for required lift coefficient

    // VSPAero setup
    double ref_area = aircraft.main_wing().area();
    double ref_span = aircraft.main_wing().span();
    double ref_chord = aircraft.main_wing().mean_geom_chord();
    double cg_x = aircraft.cg().x();
    double cg_y = aircraft.cg().y();
    double cg_z = aircraft.cg().z();
    tuple<double,double,double> cg = make_tuple(cg_x,cg_y,cg_z);    // CG position
    vector<double> mach {m_settings.vspaero_mach};
    double aoa_1 = 0;
    double aoa_2 = 10;
    vector<double> aoa {aoa_1, aoa_2};
    vector<double> beta {0};
    int wakeiter = m_settings.vspaero_wakes;
    bool symm = true;
    int threads = m_settings.vspaero_threads;
    bool stab = false;

    // create VSPAero setup
    Vsp::Aero aero {ref_area, ref_span, ref_chord, cg, mach, aoa, beta, wakeiter, symm, threads, stab,
                        m_settings.file_name(Control::File_type::tri)};

    // run VSPAero
    proc.execute(aero);

    // open for read-in polar file
    ifstream ist {m_settings.file_name(Control::File_type::main_wing_and_ht_only_vspaero_polar)};
    if(!ist) error("could not open", m_settings.file_name(Control::File_type::main_wing_and_ht_only_vspaero_polar));

    // create container of Polar data type
    vector<Vsp::Polar> vp;

    // fill container with data from the file
    fill_vector(ist,vp);

    // find the entry with AoA = 0
    auto p1 = find_if(vp.begin(),vp.end(),[](const Vsp::Polar& p){ return p.alpha==0; } );

    // assign lift coefficient value at AoA = 0
    double lift_1 = p1->lift;

    // find the entry with AoA = 10
    auto p2 = find_if(vp.begin(),vp.end(),[](const Vsp::Polar& p){ return p.alpha==10; } );

    // assign lift coefficient value at AoA = 10
    double lift_2 = p2->lift;

    double lift_cruise = aircraft.lift_coef_cruise();

    double aoa_cruise{};

    // interpolate AoA required to reach cruise lift
    aoa_cruise = ( lift_cruise - lift_1 ) * ( aoa_2 - aoa_1 ) / ( lift_2 - lift_1 ) + aoa_1;

    vector<double> aoa_cr {aoa_cruise};

    // create vspaero setup for cruise AoA analysis
    Vsp::Aero aero_cruise {ref_area, ref_span, ref_chord, cg, mach, aoa_cr, beta, wakeiter, symm, threads, stab,
                            m_settings.file_name(Control::File_type::main_wing_and_ht_only_degen_geom_csv)};

    // run vspaero analysis
    proc.execute(aero_cruise);

    // open vspaero polar file for read-in
    ifstream ist_c {m_settings.file_name(Control::File_type::main_wing_and_ht_only_vspaero_polar)};
    if(!ist_c) error("could not open", m_settings.file_name(Control::File_type::main_wing_and_ht_only_vspaero_polar));

    vector<Vsp::Polar> vp_cruise;

    fill_vector(ist_c,vp_cruise);

    // assign Oswald's factor
    if(vp_cruise.size()==1){

        aircraft.set_oswald(vp_cruise[0].oswald);
    }
}

// Horizontal Stabilizer Sizing
// Function expects aircraft as argument to size HTP and move Main Wing
// Function expects results instance as argument to report iterations
bool Analysis::vsp_horiz_stab_sizing(Vehicle::Aircraft& aircraft)
{
    cout << "VSP Horizontal Stab sizing\n";

    double min_area_ratio = 0.1;    // lower bound for Horizontal Tail Plane (HTP) to Main Wing (MW) areas ratio
    double max_area_ratio = 0.4;    // upper bound for Horizontal Tail Plane (HTP) to Main Wing (MW) areas ratio
    double small_horiz_stab_to_wing_ratio = min_area_ratio; // current small value for small HTP to MW ratio
    double big_horiz_stab_to_wing_ratio = max_area_ratio;   // current big value for small HTP to MW ratio
    double fwd_cg_limit_small_stab; // fwd cg limit allowed by small HTP
    double aft_cg_limit_small_stab; // aft cg limit allowed by small HTP
    double fwd_cg_limit_big_stab;   // fwd cg limit allowed by big HTP
    double aft_cg_limit_big_stab;   // aft cg limit allowed by big HTP

    // 10 iterations limit to stop process in case of bad convergence
    for(int i{}; i<20; ++i){

        cout << "Iteration = " << i + 1 << '\n';

        // instance for results reporting
        Horiz_stab_sizing sizing;

        sizing.wing_pos = aircraft.main_wing().loc().x();
        sizing.main_wing_aerod_center_pos = aircraft.main_wing().aerod_center_loc_x();
        sizing.main_wing_mean_geom_chord = aircraft.main_wing().mean_geom_chord();
        sizing.cg_pos = aircraft.cg().x();
        sizing.horiz_tail_aerod_center_pos = aircraft.horiz_tail().aerod_center_loc_x();
        sizing.small_stab_area_ratio = small_horiz_stab_to_wing_ratio;
        sizing.big_stab_area_ratio = big_horiz_stab_to_wing_ratio;

        // calculate fwd and aft cg limits for small HTP
        cg_limits(aircraft, small_horiz_stab_to_wing_ratio, fwd_cg_limit_small_stab, aft_cg_limit_small_stab);

        sizing.small_stab_fwd_cg_limit = fwd_cg_limit_small_stab;
        sizing.small_stab_aft_cg_limit = aft_cg_limit_small_stab;

        // calculate fwd and aft cg limits for big HTP
        cg_limits(aircraft, big_horiz_stab_to_wing_ratio, fwd_cg_limit_big_stab, aft_cg_limit_big_stab);

        sizing.big_stab_fwd_cg_limit = fwd_cg_limit_big_stab;
        sizing.big_stab_aft_cg_limit = aft_cg_limit_big_stab;

        cout << "(Sh/Sw)_small = " << small_horiz_stab_to_wing_ratio << '\n';
        cout << "(Xcg-cg_fwd/Cmac)_small = " << fwd_cg_limit_small_stab << '\n';
        cout << "(Xcg-cg_aft/Cmac)_small = " << aft_cg_limit_small_stab << '\n';

        cout << "(Sh/Sw)_big = " << big_horiz_stab_to_wing_ratio << '\n';
        cout << "(Xcg-cg_fwd/Cmac)_big = " << fwd_cg_limit_big_stab << '\n';
        cout << "(Xcg-cg_aft/Cmac)_big = " << aft_cg_limit_big_stab << '\n';

        // forward limit requirement
        double req_fwd_cg_lim = aircraft.fwd_cg_limit();

        // required HTP to MW area ratio to satisfy trim condition
        double trim_req_stab_ratio = ( big_horiz_stab_to_wing_ratio - small_horiz_stab_to_wing_ratio ) /
                                        ( fwd_cg_limit_big_stab - fwd_cg_limit_small_stab ) *
                                        ( req_fwd_cg_lim - fwd_cg_limit_small_stab ) +
                                        small_horiz_stab_to_wing_ratio;

        cout << "(Sh/Sw)_trim = " << trim_req_stab_ratio << '\n';

        sizing.trim_req_stab_area_ratio = trim_req_stab_ratio;

        // aft limit requirement
        double req_aft_cg_lim = aircraft.aft_cg_limit();

        // required HTP to MW area ratio to satisfy static stability condition
        double stat_stab_req_stab_ratio = ( big_horiz_stab_to_wing_ratio - small_horiz_stab_to_wing_ratio ) /
                                            ( aft_cg_limit_big_stab - aft_cg_limit_small_stab ) *
                                            ( req_aft_cg_lim - aft_cg_limit_small_stab ) +
                                            small_horiz_stab_to_wing_ratio;

        cout << "(Sh/Sw)_stab = " << stat_stab_req_stab_ratio << '\n';

        sizing.static_stab_req_stab_area_ratio = stat_stab_req_stab_ratio;

        // add instance of HTP sizing report to results
        m_results.add_horiz_stab_sizing(sizing);

        // find bigger and smaller HTP
        double big_stab = max(trim_req_stab_ratio,stat_stab_req_stab_ratio);
        double small_stab = min(trim_req_stab_ratio,stat_stab_req_stab_ratio);

        // check if bigger and smaller HTP within lower and upper bound
        // if not use lower or upper bound correspondingly instead of obtained area ratios
        if(big_stab < max_area_ratio && big_stab > min_area_ratio)
            big_horiz_stab_to_wing_ratio = big_stab;
        if(small_stab > min_area_ratio && small_stab < max_area_ratio)
            small_horiz_stab_to_wing_ratio = small_stab;

        cout << "New (Sh/Sw)_small = " << small_horiz_stab_to_wing_ratio << '\n';
        cout << "New (Sh/Sw)_big = " << big_horiz_stab_to_wing_ratio << '\n';


        // difference between HTP area ratios required to allow required CG envelope
        double diff = stat_stab_req_stab_ratio - trim_req_stab_ratio;


        cout << "(Sh/Sw)_stab - (Sh/Sw)_trim = " << diff << '\n';

        // use Mean Geometric Chord (MGC) as a gain to obtain new wing position
        // - multiplying difference by MGC

        // gain used for better convergence
        double shift_gain = 1.6;

        double wing_shift = 0.5 * shift_gain * diff * aircraft.main_wing().mean_geom_chord();

        // protection against high shift in case of error results
        if( wing_shift == 0 || wing_shift > abs(aircraft.fuselage().length()) )
            return false;

        cout << "dX_wing = " << wing_shift << '\n';

       // relative difference
        double rel_diff = abs( ( stat_stab_req_stab_ratio - trim_req_stab_ratio ) /
                               stat_stab_req_stab_ratio * 100 );

        // stop iterations when required HTP to main wing ratios (trim and static stability)
        // difference is smaller than 0.005
        if(abs(rel_diff) < 1){

            cout << "Horizontal Stabilizer Sizing Success\n";

            // update stab area
            double area = aircraft.main_wing().area() * big_horiz_stab_to_wing_ratio;

            // key value set to replace values in the VSP script
            map<string,string> key_value_set;
            key_value_set["\\$file_name"] = m_settings.file_name(Control::File_type::vsp_new);
            key_value_set["\\$comp_name"] = aircraft.horiz_tail().id();
            key_value_set["\\$group_name"] = "WingGeom";
            key_value_set["\\$param_name"] = "TotalArea";
            key_value_set["\\$value"] = to_string(area);

            Vsp::Process proc{m_settings.vsp_dir};

            Vsp::Script modify_model{Vsp::Script::modify_geom_param,key_value_set};
            // execute script
            proc.execute(modify_model);

            mass(aircraft);
            zero_lift_drag(aircraft);
            lift_induced_drag(aircraft);

            // create xml file with report
            //m_results.outp_horiz_stab_sizing();

            return true;
        }

        // move the wing
        double new_wing_coord = aircraft.main_wing().loc().x() + wing_shift;

        // update vsp model with new main wing position
        map<string,string> key_value_set;
        key_value_set["\\$file_name"] = m_settings.file_name(Control::File_type::vsp_new);
        key_value_set["\\$comp_name"] = aircraft.main_wing().id();
        key_value_set["\\$group_name"] = "XForm";
        key_value_set["\\$param_name"] = "X_Location";
        key_value_set["\\$value"] = to_string(new_wing_coord);

        Vsp::Process proc{m_settings.vsp_dir};

        Vsp::Script modify_model{Vsp::Script::modify_geom_param,key_value_set};
        proc.execute(modify_model);

        // read updated geometry from vsp file
        Vehicle::read_geom(aircraft, m_settings.file_name(Control::File_type::vsp_new));

        // calculate aircraft mass and cg position
        mass(aircraft);
    }

    // create xml report file of iterations
    //m_results.outp_horiz_stab_sizing();

    return false;

}


// function calculates fwd and aft cg limits for given HTP area
// cg limits will be assigned to function arguments
void Analysis::cg_limits(Vehicle::Aircraft& aircraft, double stab_to_wing_ratio,
                         double& fwd_limit, double& aft_limit) const
{
    // compute HTP area
    double area = aircraft.main_wing().area() * stab_to_wing_ratio;

    // update VSP model with new HTP area
    map<string,string> key_value_set;
    key_value_set["\\$file_name"] = m_settings.file_name(Control::File_type::vsp_new);
    key_value_set["\\$comp_name"] = aircraft.horiz_tail().id();
    key_value_set["\\$group_name"] = "WingGeom";
    key_value_set["\\$param_name"] = "TotalArea";
    key_value_set["\\$value"] = to_string(area);

    Vsp::Process proc{m_settings.vsp_dir};

    Vsp::Script modify_model{Vsp::Script::modify_geom_param,key_value_set};
    proc.execute(modify_model);

    // read in updated geometry
    Vehicle::read_geom(aircraft, m_settings.file_name(Control::File_type::vsp_new));

    // mass calculation
    mass(aircraft);

    // make MW & HT model
    key_value_set["\\$file_name"] = m_settings.file_name(Control::File_type::vsp_new);
    key_value_set["\\$out_file_name"] = m_settings.file_name(Control::File_type::main_wing_and_ht_only);

    Vsp::Script vspaero_model{Vsp::Script::write_vspaero_model,key_value_set};

    proc.execute(vspaero_model);

    // run DegenGeom script to make degengeom file
    key_value_set["\\$file_name"] = m_settings.file_name(Control::File_type::main_wing_and_ht_only);

    Vsp::Script degen_geom{Vsp::Script::compute_degen_geom,key_value_set};

    proc.execute(degen_geom);

    // VSPAero setup for Static Stability Analysis (AoA = 0)
    double ref_area = aircraft.main_wing().area();
    double ref_span = aircraft.main_wing().span();
    double ref_chord = aircraft.main_wing().mean_geom_chord();
    double cg_x = aircraft.cg().x();
    double cg_y = aircraft.cg().y();
    double cg_z = aircraft.cg().z();
    tuple<double,double,double> cg = make_tuple(cg_x,cg_y,cg_z);
    vector<double> mach {m_settings.vspaero_mach};
    vector<double> aoa_stab {0, 10};
    vector<double> beta {0};
    int wakeiter = m_settings.vspaero_wakes;
    bool symm = true;
    int threads = m_settings.vspaero_threads;
    bool stab = false;


    Vsp::Aero aero_stab {ref_area, ref_span, ref_chord, cg, mach, aoa_stab, beta, wakeiter, symm, threads, stab,
                        m_settings.file_name(Control::File_type::main_wing_and_ht_only_degen_geom_csv)};

    // run VSPAero analysis with Static Stability calculation
    proc.execute(aero_stab);

    // open VSPAero output file .stab for reading
    ifstream ist {m_settings.file_name(Control::File_type::main_wing_and_ht_only_vspaero_polar)};
    if(!ist) error("could not open", m_settings.file_name(Control::File_type::main_wing_and_ht_only_vspaero_polar));

    // vector with Stab structure to store .stab file data
    vector<Vsp::Polar> vp;

    // read file .stab file
    fill_vector(ist,vp);

    double pitch_m_coef_1 {};
    double pitch_m_coef_2 {};
    double lift_coef_1 {};
    double lift_coef_2 {};

    for( auto x : vp ){
        if(x.alpha == 0){
            pitch_m_coef_1 = x.pitch_moment;
            lift_coef_1 = x.lift;
        }
        if(x.alpha == 10){
            pitch_m_coef_2 = x.pitch_moment;
            lift_coef_2 = x.lift;
        }
    }

    double pitch_m_coef_deriv = ( pitch_m_coef_2 - pitch_m_coef_1 ) / ( 10 - 0 );
    double lift_coef_deriv = ( lift_coef_2 - lift_coef_1 ) / ( 10 - 0 );

    // calculate aft cg limit (Neutral Point location) taking into account required margin
    aft_limit = pitch_m_coef_deriv / lift_coef_deriv + m_settings.static_stability_margin;

    // vector with Lod structure to store .lod file data
    vector<Vsp::Lod> vl_stab;

    // open Lod file for reading
    ifstream ist_lod_stab {m_settings.file_name(Control::File_type::main_wing_and_ht_only_vspaero_lod)};
    if(!ist_lod_stab) error("could not open", m_settings.file_name(Control::File_type::main_wing_and_ht_only_vspaero_lod));

    // read .lod file
    fill_vector(ist_lod_stab,vl_stab);

    // HTP and MW lift coef slope is obtained by reading two HTP and MW lift values for different angles from .stab file
    // horizontal tail lift coef slope per degree alpha
    string stab_id = aircraft.horiz_tail().id();
    double stab_lift_coef_aoa_1{};
    double stab_lift_coef_aoa_2{};

    // wing lift coef slope per degree alpha
    string wing_id = aircraft.main_wing().id();
    double wing_lift_coef_aoa_1{};
    double wing_lift_coef_aoa_2{};

    // list through .stab vector
    for(auto x : vl_stab){

        // find lift results for AoA = 0
        if(x.param.mach == m_settings.vspaero_mach &&
           x.param.alpha == 0 &&
           x.param.beta == 0 &&
           x.param.roll_rate == 0 &&
           x.param.pitch_rate == 0 &&
           x.param.yaw_rate == 0){

            // find HTP by name and read lift value
            for(auto y : x.comps){
                if(y.name.compare(0,stab_id.size(),stab_id) == 0){
                    stab_lift_coef_aoa_1 += y.coef.lift;
                }
                else if(y.name.compare(0,wing_id.size(),wing_id) == 0){
                    wing_lift_coef_aoa_1 += y.coef.lift;
                }
            }
        }

        // find lift results for AoA = 0
        if(x.param.mach == m_settings.vspaero_mach &&
           x.param.alpha == 10 &&
           x.param.beta == 0 &&
           x.param.roll_rate == 0 &&
           x.param.pitch_rate == 0 &&
           x.param.yaw_rate == 0){

            // find HTP by name and read lift value
            for(auto y : x.comps){
                if(y.name.compare(0,stab_id.size(),stab_id) == 0){
                    stab_lift_coef_aoa_2 += y.coef.lift;
                }
                else if(y.name.compare(0,wing_id.size(),wing_id) == 0){
                    wing_lift_coef_aoa_2 += y.coef.lift;
                }
            }
        }
    }

    // compute HTP lift slope per degree
    double stab_lift_coef_slope = ( stab_lift_coef_aoa_2 - stab_lift_coef_aoa_1 ) / 10;

//    double wing_lift_coef_slope = ( wing_lift_coef_aoa_2 - wing_lift_coef_aoa_1 ) / 10;

    // replace VSPAero setup AoA by angle provided in settings file
    // trim analysis is performed for Max AoA provided by user
    vector<double> aoa_trim { m_settings.trim_angle_of_attack };

    // create VSPAero setup
    Vsp::Aero aero_trim {ref_area, ref_span, ref_chord, cg, mach, aoa_trim, beta, wakeiter, symm, threads, stab,
                        m_settings.file_name(Control::File_type::main_wing_and_ht_only_degen_geom_csv)};

    // run VSPAero calculation for Trim Analysis
    proc.execute(aero_trim);

    // make vector with Lod structure to read .lod file
    vector<Vsp::Lod> vl_trim;

    // open .lod file for reading
    ifstream ist_lod_trim {m_settings.file_name(Control::File_type::main_wing_and_ht_only_vspaero_lod)};
    if(!ist_lod_trim) error("could not open", m_settings.file_name(Control::File_type::main_wing_and_ht_only_vspaero_lod));

    // read .lod file
    fill_vector(ist_lod_trim,vl_trim);

    double wing_lift_coef{};
    double wing_pitch_moment_coef{};

    double stab_lift_coef{};
    double stab_pitch_moment_coef{};

    // find values for MW and HTP lift and pitch moments
    for(auto x : vl_trim){

        for(auto y : x.comps){

            if(y.name.compare(0,wing_id.size(),wing_id) == 0){
                wing_pitch_moment_coef += y.coef.y_moment;
                wing_lift_coef += y.coef.lift;
            }
            if(y.name.compare(0,stab_id.size(),stab_id) == 0){
                stab_pitch_moment_coef += y.coef.y_moment;
                stab_lift_coef += y.coef.lift;
            }
        }
    }


    // if elevator gap is unsealed horizontal stabilizer lift curve slope is reduced by 20% (Raymer 16.3)
    if(aircraft.elevator().gap()){
        cout << "CL_h_alpha 20% reduction - unsealed elevator gap\n";
        stab_lift_coef_slope = 0.8 * stab_lift_coef_slope;
    }

    // calculate HTP lift change due to elevator deflection (Raymer 16.3)
    double delta_lift_coef_horiz_tail = aircraft.elevator().delta_aoa_zero_lift() *
                                        stab_lift_coef_slope;

    // if elevator gap is unsealed lift increment due to elevator deflection is reduced by 15% (Raymer 16.3)
    if(aircraft.elevator().gap()){
        cout << "deltaCL_h_elev 15% reduction - unsealed elevator gap\n";
        delta_lift_coef_horiz_tail = 0.85 * delta_lift_coef_horiz_tail;
    }

    double flaps_lift = aircraft.delta_max_lift_coef_flaps() / 2; // due to symmetry value is halved



    // calculate adjusted total lift for elevator deflection and flaps deflection (Raymer 16.3)
    double total_lift_coef = wing_lift_coef + stab_lift_coef +
                        flaps_lift +
                        delta_lift_coef_horiz_tail;

    // pitch moment delta due to flaps deflection (Raymer 16.3)

    double flap_lever = (aircraft.main_wing().aerod_center_loc_x() - aircraft.main_wing_aerod_center_flaps()) /
                    aircraft.main_wing().mean_geom_chord();

    double delta_pitch_mom_coef_flaps = flaps_lift * flap_lever;


    // pitch moment delta due to elevator deflection (Raymer 16.3)
    double delta_pitch_mom_coef_elev = delta_lift_coef_horiz_tail *
                                    ( aircraft.cg().x() - aircraft.horiz_tail().aerod_center_loc_x() ) /
                                     aircraft.main_wing().mean_geom_chord();

    // calculate adjusted total pitch moment adding deltas to pitch moment from VSPAero analysis
    double total_pitch_moment_coef = wing_pitch_moment_coef + delta_pitch_mom_coef_flaps +
                                    stab_pitch_moment_coef + delta_pitch_mom_coef_elev;

    // calculate fwd cg limit (Xcg-Xcp)/Cmac
    fwd_limit = total_pitch_moment_coef / total_lift_coef;

}

}   // Calculation

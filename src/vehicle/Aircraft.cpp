/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Aircraft.cpp                                                                                    */
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

#include <iostream>
#include <iomanip>
#include <math.h>

#include "Aircraft.h"
#include "Wing.h"
#include "Fuselage.h"
#include "../Initial_sizing.h"
#include "../Requirements.h"
#include "../Atmosphere.h"
#include "../std_lib_facilities.h"
#include "Flaps.h"


using namespace std;

namespace Vehicle {

Aircraft::Aircraft(const Requirements& req, const Initial_sizing& init, const Design_input& des_inp)
{
    m_cruise_mach = req.cruise_mach;
    m_cruise_alt = req.cruise_alt;
    m_sfc = init.sfc;
    m_thrust = init.thrust;
    m_mass_fuel = init.fuel_mass;
    m_mass_payload = req.payload_mass;
    m_mass_operating_empty = init.op_empty_mass;
    m_mass_max_take_off = init.max_take_off_mass;
    m_ult_load_factor = req.ult_load_factor;
    m_weight_groups = init.weight_groups;

    m_main_wing_flaps = des_inp.main_wing_flaps;
    m_elevator = des_inp.elevator;

    m_fwd_cg_limit = req.fwd_cg_limit;
    m_aft_cg_limit = req.aft_cg_limit;
}

// function returns flapped area aerodynamic center x-coordinate
double Aircraft::main_wing_aerod_center_flaps() const
{
    double start_chord = m_main_wing.chord_length(m_main_wing_flaps.span_start());

    double start_chord_x = m_main_wing_flaps.span_start() *
                        m_main_wing.span() / 2 * tan( m_main_wing.sweep(0) * PI / 180 );

    double end_chord = m_main_wing.chord_length(m_main_wing_flaps.span_end());

    double taper = end_chord / start_chord;

    double mgc = ( 2.0 / 3 ) * start_chord *
                ( 1 + taper + pow( taper, 2 ) ) / ( 1 + taper ) ;

    double flap_span = ( m_main_wing_flaps.span_end() - m_main_wing_flaps.span_start() ) *
                        m_main_wing.span() / 2;

    double mgc_y = ( flap_span / 3 ) * ( ( 1 + 2 * taper ) / ( 1 + taper ) );

    double mgc_x = mgc_y * tan( m_main_wing.sweep(0) * PI / 180 );

    double aerod_center{};

    if(m_main_wing_flaps.type() == Flaps_type::slotted)
        aerod_center = 0.44 * mgc;
    else
        aerod_center = (0.5 - 0.25 * m_main_wing_flaps.chord()) * mgc;

    double ac_coord_x = aerod_center + start_chord_x + mgc_x + m_main_wing.loc().x();

    return ac_coord_x;
}

// lift coefficient increment due to flaps deflection
double Aircraft::delta_max_lift_coef_flaps() const
{
    double start_chord = m_main_wing.chord_length(m_main_wing_flaps.span_start());

    double end_chord = m_main_wing.chord_length(m_main_wing_flaps.span_end());

    double flap_span = ( m_main_wing_flaps.span_end() - m_main_wing_flaps.span_start() ) *
                        m_main_wing.span() / 2;

    double flapped_area = ( start_chord + end_chord ) * flap_span;

    double flaps_hinge_axis_angle = m_main_wing.sweep( 1 - main_wing_flaps().chord() );

    double delta = m_main_wing_flaps.delta_max_airfoil_lift_coef() *
                flapped_area / m_main_wing.area() * cos( flaps_hinge_axis_angle * PI / 180 );

    return delta;
}


double Aircraft::mass_gross() const
{
    return mass_max_take_off() - mass_fuel() / 2;
}

double Aircraft::mass_fuel() const
{
    return m_mass_max_take_off - m_mass_payload - m_mass_operating_empty;
}

double Aircraft::horiz_tail_lever() const
{
    return abs( m_main_wing.aerod_center_loc_x() -
                m_horiz_tail.aerod_center_loc_x() );
}

// returns x, y, z coordinates of the aircraft CG position
Coord_sys Aircraft::cg() const
{
    double x_m = m_fuselage.cg().x() * m_fuselage.mass() +
                m_main_wing.cg().x() * m_main_wing.mass() +
                m_horiz_tail.cg().x() * m_horiz_tail.mass() +
                m_vert_tail.cg().x() * m_vert_tail.mass();

    for(auto i : weight_groups()){

        x_m += i.cg().x() * i.mass();
    }

    double x = x_m / m_mass_operating_empty;


/*
    double x = ( m_fuselage.cg().x() * m_fuselage.mass() +
                m_main_wing.cg().x() * m_main_wing.mass() +
                m_horiz_tail.cg().x() * m_horiz_tail.mass() +
                m_vert_tail.cg().x() * m_vert_tail.mass() ) /
                m_mass_operating_empty;
*/
    double y = ( m_fuselage.cg().y() * m_fuselage.mass() +
                m_main_wing.cg().y() * m_main_wing.mass() +
                m_horiz_tail.cg().y() * m_horiz_tail.mass() +
                m_vert_tail.cg().y() * m_vert_tail.mass() ) /
                m_mass_operating_empty;

    double z = ( m_fuselage.cg().z() * m_fuselage.mass() +
                m_main_wing.cg().z() * m_main_wing.mass() +
                m_horiz_tail.cg().z() * m_horiz_tail.mass() +
                m_vert_tail.cg().z() * m_vert_tail.mass() ) /
                m_mass_operating_empty;

    return Coord_sys {x, y, z};
}

double Aircraft::lift_coef_cruise() const
{
    double lift_coef = 2 * mass_gross() * Constants::gravity /
                        ( Atmosphere::dens(m_cruise_alt) *
                         pow( cruise_speed(), 2 ) * ref_area() );

    return lift_coef;
}

double Aircraft::lift_to_drag_cruise() const
{
    return lift_coef_cruise() / total_drag_coef_cruise();
}

double Aircraft::range() const
{
    double mission_fuel_frac = 1 - mass_fuel() / mass_max_take_off();

    // all fractions are taken from Roskam
    double eng_start = 0.99;
    double taxi = 0.99;
    double take_off = 0.995;
    double climb = 0.98;
    double loiter = 1;  // currently assumed no loiter
    double descent = 0.99;
    double landing = 0.992;

    double cruise_fuel_frac = mission_fuel_frac / (eng_start * taxi *
                            take_off * climb * loiter * descent * landing);

    double sfc = m_sfc / 3600;  // convert sfc from [(kg/h)/kN] to [(kg/s)/kN]

    double breguet_range_factor = lift_to_drag_cruise() * cruise_speed() /
                                    sfc / Constants::gravity;

    double range = - breguet_range_factor * log(cruise_fuel_frac);

    return range;
}

double Aircraft::lift_induced_drag_cruise() const
{
    return pow(lift_coef_cruise(),2) / ( PI * m_oswald * m_main_wing.aspect());
}

double Aircraft::lift_induced_drag(double lift_coef) const
{
    return pow(lift_coef,2) / ( PI * m_oswald * m_main_wing.aspect());
}

double Aircraft::cruise_speed() const
{
    return m_cruise_mach * Atmosphere::speed_of_sound(m_cruise_alt);
}

double Aircraft::total_drag_coef_cruise() const
{
    return zero_lift_drag() + pow(lift_coef_cruise(),2) / ( PI * m_oswald * m_main_wing.aspect());
}

double Aircraft::total_drag_coef(double lift_coef) const
{
    return zero_lift_drag() + lift_induced_drag(lift_coef);
}

ostream& operator<<(ostream& os, Aircraft& c)
{
    int l {25};   // left column
    int r {11};   // right column

    os  << "\n--------------------------------------------\n"
        << setw(l) << left << "Aircraft:" << '\n'
        << setw(l) << left << "Cruise Mach ="           << setw(r) << left << c.cruise_mach()           << "[-]" << '\n'
        << setw(l) << left << "Cruise altitude ="       << setw(r) << left << c.cruise_alt()            << "[m]" << '\n'
        << setw(l) << left << "SFC ="                   << setw(r) << left << c.sfc()                   << "[(kg/h)/kN]" << '\n'
        << setw(l) << left << "Thrust ="                << setw(r) << left << c.thrust()                << "[kN]" << '\n'
        << setw(l) << left << "Fuel mass ="             << setw(r) << left << c.mass_fuel()             << "[kg]" << '\n'
        << setw(l) << left << "Payload mass ="          << setw(r) << left << c.mass_payload()          << "[kg]" << '\n'
        << setw(l) << left << "Operating empty mass ="  << setw(r) << left << c.mass_operating_empty()  << "[kg]" << '\n'
        << setw(l) << left << "CG:"                     << '\n' << c.cg() << '\n'
        << setw(l) << left << "Max take off mass ="     << setw(r) << left << c.mass_max_take_off()     << "[kg]" << '\n'
        << setw(l) << left << "Gross mass ="            << setw(r) << left << c.mass_gross()            << "[kg]" << '\n'
        << setw(l) << left << "Tail lever ="            << setw(r) << left << c.horiz_tail_lever()      << "[m]" << '\n'
        << setw(l) << left << "Ultimate load factor ="  << setw(r) << left << c.ult_load_factor()       << "[-]" << '\n'
        << setw(l) << left << "CL_cruise ="             << setw(r) << left << c.lift_coef_cruise()      << "[-]" << '\n'
        << setw(l) << left << "CD_0 ="                  << setw(r) << left << c.zero_lift_drag()        << "[-]" << '\n'
        << setw(l) << left << "Oswald ="                << setw(r) << left << c.oswald()                << "[-]" << '\n'
        << setw(l) << left << "CD_i ="                  << setw(r) << left << c.lift_induced_drag_cruise()     << "[-]" << '\n'
        << setw(l) << left << "L/D ="                   << setw(r) << left << c.lift_to_drag_cruise()          << "[-]" << '\n'
        << setw(l) << left << "Range ="                 << setw(r) << left << c.range()                 << "[km]" << '\n'

        << "--------------------------------------------\n"
        << setw(l) << left << "Fuselage:"               << '\n' << c.fuselage() << '\n'
        << "--------------------------------------------\n"
        << setw(l) << left << "Main wing:"              << '\n' << c.main_wing() << '\n'

        << setw(l) << left << "Flaps aerod. center ="   << setw(r) << left << c.main_wing_aerod_center_flaps() << "[m]" << '\n'
        << setw(l) << left << "Flaps dCL_max ="         << setw(r) << left << c.delta_max_lift_coef_flaps() << "[m]" << '\n'

        << "--------------------------------------------\n"
        << setw(l) << left << "Horizontal tail:"    << '\n' << c.horiz_tail() << '\n'
        << "--------------------------------------------\n"
        << setw(l) << left << "Vertical tail:"      << '\n' << c.vert_tail() << '\n';

        for(auto x : c.weight_groups()){
            os << "--------------------------------------------\n"
                << x << '\n';
        }



    return os;
}

}

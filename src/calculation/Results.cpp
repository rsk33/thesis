/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Results.cpp                                                                                     */
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
#include <vector>
#include <string>
#include <time.h>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iomanip>

#include "Results.h"
#include "../control/Settings.h"
#include "../calculation/Method.h"

#include "../../TinyXML/tinyxml2.h"

using namespace std;


namespace Calculation {

// function finds maximum criterion and correspondent variable value
// and assigns them to arguments references
// if no maximum is found function returns false
bool Results::optimum(double& var, double& crit) const
{
    auto p = max_element(m_des_study.begin(),m_des_study.end());

    if(p != m_des_study.end()){

        var = p->second;
        crit = p->first;
        return true;
    }
    else
        return false;
}

// function creates General Aircraft File (GAF) XML file
bool Results::outp_gaf(const Vehicle::Aircraft& aircraft) const
{
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLDeclaration;
    using tinyxml2::XMLComment;
    using tinyxml2::XMLNode;
    using tinyxml2::XMLElement;

    XMLDocument gaf;

    XMLDeclaration* pDec = gaf.NewDeclaration();
    pDec->SetValue("xml version=\"1.0\" encoding=\"UTF-8\"");
    gaf.InsertFirstChild(pDec);

    XMLComment* pCom = gaf.NewComment("General Aircraft File");
    gaf.InsertEndChild(pCom);

    //Get Actual Time
    time_t actTime;          // Time_t variable for actual time
    tm *now;                 // Time Structure tm for actual time
    actTime = time(0);       // initialize time_t variable
    now = localtime(&actTime);     //Get actual local time as
    stringstream date;
    date << now->tm_mday << "-" << now->tm_mon+1 << "-" << now->tm_year+1900;  //initialize stringstream with actual date (presentation: dd-mm-yyyy)
    string actualDate;
    actualDate += date.str();   //write actual Date into String actualDate

    XMLElement* pFile = gaf.NewElement("File");
    pFile->SetAttribute("Project_name", m_settings.project_name.c_str());
    pFile->SetAttribute("Creation_date", actualDate.c_str());
    gaf.InsertEndChild(pFile);

    // requirements
    XMLElement* pRequirements = gaf.NewElement("Requirements");
    pFile->InsertEndChild(pRequirements);

    XMLElement* pEle = gaf.NewElement("Range");
    pEle->SetAttribute("Value", m_req.range);
    pEle->SetAttribute("Unit", "km");
    pRequirements->InsertEndChild(pEle);

    pEle = gaf.NewElement("Payload_mass");
    pEle->SetAttribute("Value", m_req.payload_mass);
    pEle->SetAttribute("Unit", "kg");
    pRequirements->InsertEndChild(pEle);

    pEle = gaf.NewElement("Cruise_mach_number");
    pEle->SetAttribute("Value", m_req.cruise_mach);
    pEle->SetAttribute("Unit", "-");
    pRequirements->InsertEndChild(pEle);

    pEle = gaf.NewElement("Cruise_altitude");
    pEle->SetAttribute("Value", m_req.cruise_alt);
    pEle->SetAttribute("Unit", "m");
    pRequirements->InsertEndChild(pEle);

    pEle = gaf.NewElement("Ultimate_load_factor");
    pEle->SetAttribute("Value", m_req.ult_load_factor);
    pEle->SetAttribute("Unit", "-");
    pRequirements->InsertEndChild(pEle);

    XMLElement* pLoading_envelope = gaf.NewElement("Loading_envelope");
    pRequirements->InsertEndChild(pLoading_envelope);

    XMLElement* pFront_limit = gaf.NewElement("Front_limit");
    pFront_limit->SetAttribute("Value", m_req.fwd_cg_limit);
    pFront_limit->SetAttribute("Unit", "%MAC");
    pLoading_envelope->InsertEndChild(pFront_limit);

    XMLElement* pAft_limit = gaf.NewElement("Aft_limit");
    pAft_limit->SetAttribute("Value", m_req.aft_cg_limit);
    pAft_limit->SetAttribute("Unit", "%MAC");
    pLoading_envelope->InsertEndChild(pAft_limit);

    // initial sizing
    XMLElement* pInitial_sizing = gaf.NewElement("Initial_sizing");
    pFile->InsertEndChild(pInitial_sizing);

    pEle = gaf.NewElement("Ref_area");
    pEle->SetAttribute("Value", m_init.ref_area);
    pEle->SetAttribute("Unit", "m^2");
    pInitial_sizing->InsertEndChild(pEle);

    pEle = gaf.NewElement("Thrust");
    pEle->SetAttribute("Value", m_init.thrust);
    pEle->SetAttribute("Unit", "kN");
    pInitial_sizing->InsertEndChild(pEle);

    pEle = gaf.NewElement("SFC");
    pEle->SetAttribute("Value", m_init.sfc);
    pEle->SetAttribute("Unit", "(kg/h)/kN");
    pInitial_sizing->InsertEndChild(pEle);

    pEle = gaf.NewElement("Maximum_take_off_mass");
    pEle->SetAttribute("Value", m_init.max_take_off_mass);
    pEle->SetAttribute("Unit", "kg");
    pInitial_sizing->InsertEndChild(pEle);

    pEle = gaf.NewElement("Operating_empty_mass");
    pEle->SetAttribute("Value", m_init.op_empty_mass);
    pEle->SetAttribute("Unit", "kg");
    pInitial_sizing->InsertEndChild(pEle);

    pEle = gaf.NewElement("Fuel_mass");
    pEle->SetAttribute("Value", m_init.fuel_mass);
    pEle->SetAttribute("Unit", "kg");
    pInitial_sizing->InsertEndChild(pEle);

    // design study
    XMLElement* pDesign_study = gaf.NewElement("Design_study");
    pFile->InsertEndChild(pDesign_study);

    // variable
    pEle = gaf.NewElement("Variable");
    pEle->SetAttribute("Geom_name", m_settings.variable.geom_name().c_str());
    pEle->SetAttribute("Group_name", m_settings.variable.group_name().c_str());
    pEle->SetAttribute("Param_name", m_settings.variable.param_name().c_str());
    pEle->SetAttribute("Min_value", m_settings.variable.min_value());
    pEle->SetAttribute("Max_value", m_settings.variable.max_value());
    pEle->SetAttribute("Delta", m_settings.variable.delta());
    pDesign_study->InsertEndChild(pEle);

    // criterion
    pEle = gaf.NewElement("Criterion");
    pEle->SetAttribute("Parameter", m_settings.criterion.param_name().c_str());
    pEle->SetAttribute("Unit", m_settings.criterion.unit().c_str());
    pDesign_study->InsertEndChild(pEle);

    // analysis configuration
    XMLElement* pAnalysis_configuration = gaf.NewElement("Analysis_configuration");
    pDesign_study->InsertEndChild(pAnalysis_configuration);

    pEle = gaf.NewElement("Wet_area");
    pEle->SetAttribute("Method", Calculation::method_to_string(m_settings.wet_area).c_str());
    pAnalysis_configuration->InsertEndChild(pEle);

    pEle = gaf.NewElement("Weight");
    pEle->SetAttribute("Method", Calculation::method_to_string(m_settings.mass).c_str());
    pAnalysis_configuration->InsertEndChild(pEle);

    XMLElement* pDrag = gaf.NewElement("Drag");
    pAnalysis_configuration->InsertEndChild(pDrag);

    pEle = gaf.NewElement("Zero_lift_drag");
    pEle->SetAttribute("Method", Calculation::method_to_string(m_settings.zero_lift_drag).c_str());
    pDrag->InsertEndChild(pEle);

    pEle = gaf.NewElement("Lift_induced_drag");
    pEle->SetAttribute("Method", Calculation::method_to_string(m_settings.lift_induced_drag).c_str());
    pDrag->InsertEndChild(pEle);

    pEle = gaf.NewElement("Trim");
    pEle->SetAttribute("Method", Calculation::method_to_string(m_settings.trim).c_str());
    pEle->SetAttribute("Max_AoA", m_settings.trim_angle_of_attack);
    pAnalysis_configuration->InsertEndChild(pEle);

    pEle = gaf.NewElement("Static_stability");
    pEle->SetAttribute("Method", Calculation::method_to_string(m_settings.static_stability).c_str());
    pEle->SetAttribute("Margin", m_settings.static_stability_margin);
    pAnalysis_configuration->InsertEndChild(pEle);

    // results
    XMLElement* pResults = gaf.NewElement("Results");

    pDesign_study->InsertEndChild(pResults);

    // find optimal variable value pair
    double var{};
    double val{};

    optimum(var,val);

    pEle = gaf.NewElement("Variable");

    string var_param_full_name = m_settings.variable.geom_name() + ':' +
                                m_settings.variable.group_name() + ':' +
                                m_settings.variable.param_name();

    pEle->SetAttribute("Parameter", var_param_full_name.c_str());
    pEle->SetAttribute("Value", var);
    pResults->InsertEndChild(pEle);

    pEle = gaf.NewElement("Criterion");
    pEle->SetAttribute("Parameter", m_settings.criterion.param_name().c_str());

    // determine what is used as a criterion
    if(m_settings.criterion.param_name() == "Range"){
        pEle->SetAttribute("Value", aircraft.range());
    }
    else{
        pEle->SetAttribute("Value", "NaN"); // undefined
    }
    pEle->SetAttribute("Units", m_settings.criterion.unit().c_str());
    pResults->InsertEndChild(pEle);


    // save file
    string name = m_settings.file_name(Control::File_type::gaf);
    gaf.SaveFile(name.c_str());

    if(gaf.Error()) return false;

    cout << "\nGeneral Aircraft File was successfully created:\n" << name << "\n\n";

    return true;

}

// function creates xml file with results of the design with respect to range process
bool Results::outp_des_study() const
{
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLDeclaration;
    using tinyxml2::XMLElement;

    XMLDocument doc;

    XMLDeclaration* pDec = doc.NewDeclaration();
    pDec->SetValue("xml version=\"1.0\" encoding=\"UTF-8\"");
    doc.InsertFirstChild(pDec);

    XMLElement* pNode = doc.NewElement("Design_study");
    doc.InsertEndChild(pNode);

    for(int i{}; i<int(m_des_study.size()); ++i){

        XMLElement* pEle = doc.NewElement("Iteration");
        pEle->SetAttribute(m_settings.variable.full_name().c_str(), m_des_study[i].second);
        pEle->SetAttribute("LD_cruise", m_range_des_reports[i].lift_to_drag_cruise);
        pEle->SetAttribute("M_MTOM", m_range_des_reports[i].mass_max_take_off);
        pEle->SetAttribute("M_OEM", m_range_des_reports[i].mass_oper_empty);
        pEle->SetAttribute("M_fus", m_range_des_reports[i].mass_fus);
        pEle->SetAttribute("M_wing", m_range_des_reports[i].mass_wing);
        pEle->SetAttribute("M_horiz_tail", m_range_des_reports[i].mass_horiz_tail);
        pEle->SetAttribute("M_vert_tail", m_range_des_reports[i].mass_vert_tail);
        pEle->SetAttribute("M_sys", m_range_des_reports[i].mass_sys);
        pEle->SetAttribute("M_F", m_range_des_reports[i].mass_fuel);
        pEle->SetAttribute("M_PL", m_range_des_reports[i].mass_payload);

        pEle->SetAttribute(m_settings.criterion.param_name().c_str(), m_des_study[i].first);
        pNode->InsertEndChild(pEle);
    }

    string induced_drag_method = method_to_string(m_settings.lift_induced_drag);

    string name =  m_settings.file_name(Control::File_type::outp_dir) +
               m_settings.project_name + "_des_study.xml";

    doc.SaveFile(name.c_str());

    if(doc.Error()) return false;

    cout << "\nOptimization File was successfully created:\n" << name << "\n\n";

    return true;
}

// functions outputs xml file with polar
bool Results::outp_polar() const
{
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLDeclaration;
    using tinyxml2::XMLElement;

    XMLDocument doc;

    XMLDeclaration* pDec = doc.NewDeclaration();
    pDec->SetValue("xml version=\"1.0\" encoding=\"UTF-8\"");
    doc.InsertFirstChild(pDec);

    XMLElement* pNode = doc.NewElement("Var_polars");

    doc.InsertEndChild(pNode);

    string variable_name = m_settings.variable.full_name();

    for(auto x : m_var_polars){

        XMLElement* pVar_polar = doc.NewElement("Var_polar");
        pVar_polar->SetAttribute(variable_name.c_str(), x.var);
        pNode->InsertEndChild(pVar_polar);

        for(auto y : x.polars){

            XMLElement* pPair = doc.NewElement("Pair");
            pPair->SetAttribute("Lift", y.lift);
            pPair->SetAttribute("Drag", y.drag);
            pVar_polar->InsertEndChild(pPair);
        }

    }

    string induced_drag_method = method_to_string(m_settings.lift_induced_drag);

    string name =  m_settings.file_name(Control::File_type::outp_dir) +
                   m_settings.project_name + "_polar.xml";

    doc.SaveFile(name.c_str());

    if(doc.Error()) return false;

    cout << "\nPolar File was successfully created:\n" << name << "\n\n";

    return true;

}

// function shows to console design with respect to range results
void Results::show_des_study() const
{
    int l {35};   // left column
    int r {11};   // right column

    cout << setw(l) << left << m_settings.variable.full_name()
        << setw(r) << left << m_settings.criterion.param_name() << '\n';

    for(auto x : m_des_study){

        cout << setw(l) << left << x.second << setw(r) << left << x.first << '\n';
    }

    auto p = max_element(m_des_study.begin(),m_des_study.end());

    cout << "Optimum" << '\n'
        << setw(l) << left << p->second
        << setw(r) << left << p->first << '\n';

}

// function adds a polar for a current variable value
void Results::add_polar(const Vehicle::Aircraft& aircraft, double variable)
{
    double lift_coef{};

    vector<Pol> polar;

    while(lift_coef < 2){

        double drag_coef = aircraft.total_drag_coef(lift_coef);
        polar.push_back(Pol{lift_coef,drag_coef});

        lift_coef += 0.1;
    }

    m_var_polars.push_back(Var_polars{variable,polar});
}

// function creates xml file with of horizontal stabilizer sizing report
bool Results::outp_horiz_stab_sizing() const
{
    cout << "Writing Horizontal Stabilizer Sizing File\n";

    using tinyxml2::XMLDocument;
    using tinyxml2::XMLDeclaration;
    using tinyxml2::XMLElement;

    XMLDocument doc;

    XMLDeclaration* pDec = doc.NewDeclaration();
    pDec->SetValue("xml version=\"1.0\" encoding=\"UTF-8\"");
    doc.InsertFirstChild(pDec);

    XMLElement* pNode = doc.NewElement("Horizontal_stabilizer_sizing");

    doc.InsertEndChild(pNode);

    XMLElement* pRequirement = doc.NewElement("Requirement");
    pRequirement->SetAttribute("Fwd_cg_limit", m_req.fwd_cg_limit);
    pRequirement->SetAttribute("Aft_cg_limit", m_req.aft_cg_limit);
    pRequirement->SetAttribute("Margin", m_settings.static_stability_margin);
    pNode->InsertEndChild(pRequirement);

    for(int i{}; i<int(m_horiz_stab_sizing.size()); ++i){

        int iter = i + 1;

        XMLElement* pIteration = doc.NewElement("Iteration");
        pIteration->SetAttribute("Iteration", iter);
        pIteration->SetAttribute("Wing_pos", m_horiz_stab_sizing[i].wing_pos);
        pIteration->SetAttribute("Main_wing_aerod_center_pos", m_horiz_stab_sizing[i].main_wing_aerod_center_pos);
        pIteration->SetAttribute("Main_wing_mean_geom_chord", m_horiz_stab_sizing[i].main_wing_mean_geom_chord);
        pIteration->SetAttribute("Cg_pos", m_horiz_stab_sizing[i].cg_pos);
        pIteration->SetAttribute("Horiz_stab_aerod_center_pos", m_horiz_stab_sizing[i].horiz_tail_aerod_center_pos);
        pIteration->SetAttribute("Small_stab_area_ratio", m_horiz_stab_sizing[i].small_stab_area_ratio);
        pIteration->SetAttribute("Big_stab_area_ratio", m_horiz_stab_sizing[i].big_stab_area_ratio);
        pIteration->SetAttribute("Small_stab_fwd_cg_limit", m_horiz_stab_sizing[i].small_stab_fwd_cg_limit);
        pIteration->SetAttribute("Small_stab_aft_cg_limit", m_horiz_stab_sizing[i].small_stab_aft_cg_limit);
        pIteration->SetAttribute("Big_stab_fwd_cg_limit", m_horiz_stab_sizing[i].big_stab_fwd_cg_limit);
        pIteration->SetAttribute("Big_stab_aft_cg_limit", m_horiz_stab_sizing[i].big_stab_aft_cg_limit);
        pIteration->SetAttribute("Trim_req_stab_area_ratio", m_horiz_stab_sizing[i].trim_req_stab_area_ratio);
        pIteration->SetAttribute("Static_stab_req_stab_area_ratio", m_horiz_stab_sizing[i].static_stab_req_stab_area_ratio);

        double diff = abs( m_horiz_stab_sizing[i].static_stab_req_stab_area_ratio -
                        m_horiz_stab_sizing[i].trim_req_stab_area_ratio );

        pIteration->SetAttribute("Abs_diff", diff);

        double rel_diff = abs( diff / m_horiz_stab_sizing[i].static_stab_req_stab_area_ratio ) * 100;

        pIteration->SetAttribute("Rel_diff", rel_diff);

        pNode->InsertEndChild(pIteration);

    }

    string name =  m_settings.file_name(Control::File_type::outp_dir) +
                   m_settings.project_name + "_horiz_stab_sizing.xml";

    doc.SaveFile(name.c_str());

    if(doc.Error()) return false;

    cout << "\nHorizontal Stabilizer Sizing File was successfully created:\n" << name << "\n\n";

    return true;

}

}   // Calculation

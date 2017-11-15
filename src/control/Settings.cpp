/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Settings.cpp                                                                                    */
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

#include <iomanip>
#include <iostream>
#include <string>

#include "Settings.h"
#include "Variable.h"
#include "Criterion.h"
#include "File_type.h"

#include "../calculation/Method.h"
#include "../vsp/Process.h"

#include "../std_lib_facilities.h"
#include "../../TinyXML/tinyxml2.h"

using namespace std;

namespace Control {


// function returns file relative address and name for certain file type
string Settings::file_name(const File_type& file_fype) const
{
    // name contains relative address same for all files
    string input_dir_rel_path = "projects/" + project_name + "/input/";
    string output_dir_rel_path = "projects/" + project_name + "/output/";

    // add file extension
    switch (file_fype) {
    case File_type::settings:
        return input_dir_rel_path + "project_settings_file.xml";

    case File_type::outp_dir:
        return output_dir_rel_path;

    case File_type::requirements:
        return input_dir_rel_path + "requirements.xml";

    case File_type::initial_sizing:
        return input_dir_rel_path + "initial_sizing.xml";

    case File_type::design_input:
        return input_dir_rel_path + "design.xml";

    case File_type::gaf:
        return output_dir_rel_path + project_name + ".gaf";

    case File_type::vsp:
        return input_dir_rel_path + project_name + ".vsp3";

    case File_type::vsp_new:
        return output_dir_rel_path + project_name + "_optimal.vsp3";

    case File_type::main_wing_and_ht_only:
        return output_dir_rel_path + project_name + "_MainWing&HT_Only.vsp3";

    case File_type::comp_geom_csv:
        return output_dir_rel_path + project_name + "_optimal_CompGeom.csv";

    case File_type::comp_geom_txt:
        return output_dir_rel_path + project_name + "_optimal_CompGeom.txt";

    case File_type::degen_geom:
        return output_dir_rel_path + project_name + "_optimal_DegenGeom";

    case File_type::degen_geom_csv:
        return output_dir_rel_path + project_name + "_optimal_DegenGeom.csv";

    case File_type::main_wing_and_ht_only_degen_geom_csv:
        return output_dir_rel_path + project_name + "_MainWing&HT_Only_DegenGeom.csv";

    case File_type::vspaero_vspaero:
        return output_dir_rel_path + project_name + "_optimal_DegenGeom.vspaero";

    case File_type::vspaero_polar:
        return output_dir_rel_path + project_name + "_optimal_DegenGeom.polar";

    case File_type::vspaero_stab:
        return output_dir_rel_path + project_name + "_optimal_DegenGeom.stab";

    case File_type::vspaero_adb:
        return output_dir_rel_path + project_name + "_optimal_DegenGeom.adb";

    case File_type::vspaero_adb_cases:
        return output_dir_rel_path + project_name + "_optimal_DegenGeom.adb.cases";

    case File_type::vspaero_fem:
        return output_dir_rel_path + project_name + "_optimal_DegenGeom.fem";

    case File_type::vspaero_history:
        return output_dir_rel_path + project_name + "_optimal_DegenGeom.history";

    case File_type::vspaero_lod:
        return output_dir_rel_path + project_name + "_optimal_DegenGeom.lod";

    case File_type::tri:
        return output_dir_rel_path + project_name + ".tri";

    case File_type::main_wing_and_ht_only_vspaero_vspaero:
        return output_dir_rel_path + project_name + "_MainWing&HT_Only_DegenGeom.vspaero";

    case File_type::main_wing_and_ht_only_vspaero_polar:
        return output_dir_rel_path + project_name + "_MainWing&HT_Only_DegenGeom.polar";

    case File_type::main_wing_and_ht_only_vspaero_stab:
        return output_dir_rel_path + project_name + "_MainWing&HT_Only_DegenGeom.stab";

    case File_type::main_wing_and_ht_only_vspaero_adb:
        return output_dir_rel_path + project_name + "_MainWing&HT_Only_DegenGeom.adb";

    case File_type::main_wing_and_ht_only_vspaero_adb_cases:
        return output_dir_rel_path + project_name + "_MainWing&HT_Only_DegenGeom.adb.cases";

    case File_type::main_wing_and_ht_only_vspaero_fem:
        return output_dir_rel_path + project_name + "_MainWing&HT_Only_DegenGeom.fem";

    case File_type::main_wing_and_ht_only_vspaero_history:
        return output_dir_rel_path + project_name + "_MainWing&HT_Only_DegenGeom.history";

    case File_type::main_wing_and_ht_only_vspaero_lod:
        return output_dir_rel_path + project_name + "_MainWing&HT_Only_DegenGeom.lod";

    default:
        throw invalid_argument("file_fype");
    }
}


//--- class Settings member functions ---//

// prints settings set to console
ostream& operator<<(ostream& os, Settings& s)
{
    int l {30};
    // print set of settings
    os << "==============================================================================\n"
        << "Settings\n\n"
        << setw(l) << left << "Project name:" << s.project_name << '\n'
        << setw(l) << left << "VSP address:" << s.vsp_dir << '\n'
        << setw(l) << left << "VSPAero threads number:" << s.vspaero_threads << '\n'
        << setw(l) << left << "VSPAero wakes number:" << s.vspaero_wakes << '\n'
        << setw(l) << left << "VSPAero Mach number:" << s.vspaero_mach << '\n'
//        << setw(l) << left << "Geom input method:" << Calculation::method_to_string(s.geom_input) << '\n'
        << s.variable << '\n'
        << s.criterion << '\n'
        << setw(l) << left << "Wet area method:" << Calculation::method_to_string(s.wet_area) << '\n'
        << setw(l) << left << "Weight method:" << Calculation::method_to_string(s.mass) << '\n'
        << setw(l) << left << "Zero lift drag method:" << Calculation::method_to_string(s.zero_lift_drag) << '\n'
        << setw(l) << left << "Lift induced drag method:" << Calculation::method_to_string(s.lift_induced_drag) << '\n'
        << setw(l) << left << "Trim method:" << Calculation::method_to_string(s.trim) << '\n'
        << setw(l) << left << "Trim AoA:" << s.trim_angle_of_attack << '\n'
        << setw(l) << left << "Static stability method:" << Calculation::method_to_string(s.static_stability) << '\n'
        << setw(l) << left << "Static stability margin:" << s.static_stability_margin << '\n';

    return os;
}

// function reads settings from xml file
Settings::Settings(const string& file_nam)
{
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLNode;
    using tinyxml2::XMLElement;

    // reading general settings
    XMLDocument gen_set;

    gen_set.LoadFile(file_nam.c_str());

    if(gen_set.Error()) error("Could not open XML-File ", file_nam);

    XMLNode* pSettings = gen_set.FirstChildElement();

    if(pSettings == NULL) error("Could not access Settings Node");

    // read project name
    XMLElement* pProject_name = pSettings->FirstChildElement("Project_name");

    if(pProject_name == NULL) error("Could not access Project_name Element");

    project_name = pProject_name->Attribute("Value");


    // read OpenVSP path

    XMLElement* pOpenVSP = pSettings->FirstChildElement("OpenVSP");

    if(pOpenVSP == NULL) error("Could not access OpenVSP Element");

    XMLElement* pPath = pOpenVSP->FirstChildElement("Path");

    if(pPath == NULL) error("Could not access Path Element");

    XMLElement* pItem = pPath->FirstChildElement("Item");

    if(pItem == NULL) error("Could not access Item Element");

    // multiple vsp addresses can be stored under node VSP_dir
    // algorithm is checking one by one each address until
    // vspscript.exe is found and stores this address

    while(true)
    {
        vsp_dir = pItem->Attribute("Value");

        // check if vsp could be launched on using address
        string arg = vsp_dir + "vspscript";

        if(Vsp::command_line(arg))                // check if OpenVSP can be launched
        {
            break;
        }
        else
        {
            // check other addresses
            pItem = pItem->NextSiblingElement("Item");

            // none of listed address contains vspscript.exe - report error
            if(pItem == NULL) error("vspscript.exe could not be found");
        }
    }

    XMLElement* pVSPAero = pOpenVSP->FirstChildElement("VSPAero");

    if(pVSPAero == NULL) error("Could not access VSPAero Element");

    XMLElement* pThreads = pVSPAero->FirstChildElement("Threads");

    if(pThreads == NULL) error("Could not access Threads Element");

    pThreads->QueryIntAttribute("Number", &vspaero_threads);

    XMLElement* pWakes = pVSPAero->FirstChildElement("Wakes");

    if(pWakes == NULL) error("Could not access Wakes Element");

    pWakes->QueryIntAttribute("Number", &vspaero_wakes);

    XMLElement* pMach = pVSPAero->FirstChildElement("Mach");

    if(pMach == NULL) error("Could not access Mach Element");

    pMach->QueryDoubleAttribute("Number", &vspaero_mach);

    // Read Project specific settings

    XMLDocument proj_set;

    string proj_set_name = file_name(Control::File_type::settings);

    proj_set.LoadFile(proj_set_name.c_str());

    if(proj_set.Error()) error("Could not open XML-File ", proj_set_name);

    pSettings = proj_set.FirstChildElement();

    if(pSettings == NULL) error("Could not access Settings Node");

    // read variable

    XMLElement* pVariable = pSettings->FirstChildElement("Variable");

    if(pVariable == NULL) error("Could not access Variable Element");

    string geom_name = pVariable->Attribute("Geom_name");

    string group_name = pVariable->Attribute("Group_name");

    string param_name = pVariable->Attribute("Param_name");

    double min_value;

    pVariable->QueryDoubleAttribute("Min_value", &min_value);

    double max_value;

    pVariable->QueryDoubleAttribute("Max_value", &max_value);

    double delta;

    pVariable->QueryDoubleAttribute("Delta", &delta);

    variable = Variable{geom_name, group_name, param_name, min_value, max_value, delta};

    // read criterion

    XMLElement* pCriterion = pSettings->FirstChildElement("Criterion");

    if(pCriterion == NULL) error("Could not access Criterion Element");

    string parameter = pCriterion->Attribute("Parameter");

    string unit = pCriterion->Attribute("Unit");

    criterion = Criterion{parameter, unit};

    // read analysis configuration

    XMLElement* pAnalysis_configuration = pSettings->FirstChildElement("Analysis_configuration");

    if(pAnalysis_configuration == NULL) error("Could not access Analysis_configuration Element");

    // wet area calculation

    XMLElement* pWet_area = pAnalysis_configuration->FirstChildElement("Wet_area");

    if(pWet_area == NULL) error("Could not access Wet_area Element");

    string method = pWet_area->Attribute("Method");

    wet_area = Calculation::string_to_method(method);

    // weight calculation

    XMLElement* pWeight = pAnalysis_configuration->FirstChildElement("Weight");

    if(pWeight == NULL) error("Could not access Weight Element");

    method = pWeight->Attribute("Method");

    mass = Calculation::string_to_method(method);

    // drag calculation

    XMLElement* pDrag = pAnalysis_configuration->FirstChildElement("Drag");

    if(pDrag == NULL) error("Could not access Drag Element");

    XMLElement* pZero_lift = pDrag->FirstChildElement("Zero_lift");

    if(pZero_lift == NULL) error("Could not access Zero_lift Element");

    method = pZero_lift->Attribute("Method");

    zero_lift_drag = Calculation::string_to_method(method);

    XMLElement* pLift_induced = pDrag->FirstChildElement("Lift_induced");

    if(pLift_induced == NULL) error("Could not access Lift_induced Element");

    method = pLift_induced->Attribute("Method");

    lift_induced_drag = Calculation::string_to_method(method);

    // trim

    XMLElement* pTrim = pAnalysis_configuration->FirstChildElement("Trim");

    if(pTrim == NULL) error("Could not access Trim Element");

    method = pTrim->Attribute("Method");

    trim = Calculation::string_to_method(method);

    pTrim->QueryDoubleAttribute("Max_AoA", &trim_angle_of_attack);

    // static stability

    XMLElement* pStatic_stability = pAnalysis_configuration->FirstChildElement("Static_stability");

    if(pStatic_stability == NULL) error("Could not access Static_stability Element");

    method = pStatic_stability->Attribute("Method");

    static_stability = Calculation::string_to_method(method);

    pStatic_stability->QueryDoubleAttribute("Margin", &static_stability_margin);

}

// function deletes temporary files
void Settings::delete_temp_files() const
{
    remove(file_name(Control::File_type::comp_geom_csv).c_str());
    remove(file_name(Control::File_type::comp_geom_txt).c_str());
    remove(file_name(Control::File_type::main_wing_and_ht_only_vspaero_polar).c_str());
    remove(file_name(Control::File_type::main_wing_and_ht_only_vspaero_adb).c_str());
    remove(file_name(Control::File_type::main_wing_and_ht_only_vspaero_adb_cases).c_str());
    remove(file_name(Control::File_type::main_wing_and_ht_only_vspaero_fem).c_str());
    remove(file_name(Control::File_type::main_wing_and_ht_only_vspaero_history).c_str());
    remove(file_name(Control::File_type::main_wing_and_ht_only_vspaero_lod).c_str());
    remove(file_name(Control::File_type::main_wing_and_ht_only_vspaero_vspaero).c_str());
    remove(file_name(Control::File_type::main_wing_and_ht_only_degen_geom_csv).c_str());
    remove(file_name(Control::File_type::main_wing_and_ht_only).c_str());

}

}   // end of Control

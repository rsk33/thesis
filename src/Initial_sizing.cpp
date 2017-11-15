/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Initial_sizing.cpp                                                                              */
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
#include "Initial_sizing.h"
#include "std_lib_facilities.h"
#include "../TinyXML/tinyxml2.h"

using namespace std;

//===============================================================================================
//=== class Initial_sizing member functions ===//

// Reads in Initial Sizing Parameters from XML
Initial_sizing::Initial_sizing(const string& file_name)
{
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLNode;
    using tinyxml2::XMLElement;

    XMLDocument doc;
    doc.LoadFile(file_name.c_str());
    if(doc.Error()) error("Could not open Initial Sizing File", file_name);


    XMLElement* pInitital_sizing = doc.FirstChildElement();
    if(pInitital_sizing == NULL) error("Could not access Initital_sizing Node");


    XMLElement* pRef_area = pInitital_sizing->FirstChildElement("Ref_area");
    if(pRef_area == NULL) error("Could not access Ref_area Node");
    pRef_area->QueryDoubleAttribute("Value", &ref_area);


    XMLElement* pThrust = pInitital_sizing->FirstChildElement("Thrust");
    if(pThrust == NULL) error("Could not access Thrust Node");
    pThrust->QueryDoubleAttribute("Value", &thrust);


    XMLElement* pSFC = pInitital_sizing->FirstChildElement("SFC");
    if(pSFC == NULL) error("Could not access SFC Node");
    pSFC->QueryDoubleAttribute("Value", &sfc);


    XMLElement* pMaximum_take_off_mass = pInitital_sizing->FirstChildElement("Maximum_take_off_mass");
    if(pMaximum_take_off_mass == NULL) error("Could not access Maximum_take_off_mass Node");
    pMaximum_take_off_mass->QueryDoubleAttribute("Value", &max_take_off_mass);


    XMLElement* pOperating_empty_mass = pInitital_sizing->FirstChildElement("Operating_empty_mass");
    if(pOperating_empty_mass == NULL) error("Could not access Operating_empty_mass Node");
    pOperating_empty_mass->QueryDoubleAttribute("Value", &op_empty_mass);


    XMLElement* pFuel_mass = pInitital_sizing->FirstChildElement("Fuel_mass");
    if(pFuel_mass == NULL) error("Could not access Fuel_mass Node");
    pFuel_mass->QueryDoubleAttribute("Value", &fuel_mass);

    XMLElement* pWeight_groups = pInitital_sizing->FirstChildElement("Weight_groups");
    if(pFuel_mass == NULL) error("Could not access Weight_groups");

    XMLElement* pItem = pWeight_groups->FirstChildElement("Item");

    // read weight groups
    while(pItem != NULL){

        string name;
        name = pItem->Attribute("Name");

        double mass;
        pItem->QueryDoubleAttribute("Mass", &mass);

        double cg_x;
        pItem->QueryDoubleAttribute("CG_x", &cg_x);

        Vehicle::Component comp {name};

        comp.set_mass(mass);

        comp.set_cg(Vehicle::Coord_sys{cg_x,0,0});

        weight_groups.push_back(comp);

        pItem = pItem->NextSiblingElement("Item");

    }

}

// writes Parameters to Console
ostream& operator<<(ostream& os, Initial_sizing& init)
{
    int a {30};   // left column
    int b {11};   // right column
    os << "==============================================================================\n"
        << "Initial Sizing\n\n"
        << setw(a) << left << "Reference area:"         << setw(b) << left << init.ref_area << "[m^2]" << '\n'
        << setw(a) << left << "Thrust:"                 << setw(b) << left << init.thrust << "[kN]" << '\n'
        << setw(a) << left << "SFC:"                    << setw(b) << left << init.sfc << "[(kg/h)/kN]" << '\n'
        << setw(a) << left << "Max Take-Off mass:"      << setw(b) << left << init.max_take_off_mass << "[kg]" << '\n'
        << setw(a) << left << "Operating Empty mass:"   << setw(b) << left << init.op_empty_mass << "[kg]" << '\n'
        << setw(a) << left << "Fuel mass:"              << setw(b) << left << init.fuel_mass << "[kg]" << '\n';

    return os;
}


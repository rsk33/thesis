/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Requirements.cpp                                                                                */
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

#include "Requirements.h"
#include "../TinyXML/tinyxml2.h"
#include "std_lib_facilities.h"

using namespace std;



//===============================================================================================
//=== class Requirements member functions ===//

// read-in requirements xml file
Requirements::Requirements(const string& file_name)
{
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLNode;
    using tinyxml2::XMLElement;

    XMLDocument doc;
    doc.LoadFile(file_name.c_str());
    if(doc.Error()) error("Could not open Initial Sizing File", file_name);

    XMLElement* pRequirements = doc.FirstChildElement();
    if(pRequirements == NULL) error("Could not access Requirements Node");

    XMLElement* pEle = pRequirements->FirstChildElement("Range");
    if(pEle == NULL) error("Could not access Range Node");
    pEle->QueryDoubleAttribute("Value", &range);

    pEle = pRequirements->FirstChildElement("Payload_mass");
    if(pEle == NULL) error("Could not access Payload_mass Node");
    pEle->QueryDoubleAttribute("Value", &payload_mass);

    pEle = pRequirements->FirstChildElement("Cruise_mach_number");
    if(pEle == NULL) error("Could not access Cruise_mach_number Node");
    pEle->QueryDoubleAttribute("Value", &cruise_mach);

    pEle = pRequirements->FirstChildElement("Cruise_altitude");
    if(pEle == NULL) error("Could not access Cruise_altitude Node");
    pEle->QueryDoubleAttribute("Value", &cruise_alt);

    pEle = pRequirements->FirstChildElement("Ultimate_load_factor");
    if(pEle == NULL) error("Could not access Ultimate_load_factor Node");
    pEle->QueryDoubleAttribute("Value", &ult_load_factor);

    XMLElement* pLoading_envelope = pRequirements->FirstChildElement("Loading_envelope");
    if(pEle == NULL) error("Could not access Loading_envelope Node");

    XMLElement* pFront_cg_limit = pLoading_envelope->FirstChildElement("Front_CG_limit");
    if(pFront_cg_limit == NULL) error("Could not access Front_CG_limit Node");
    pFront_cg_limit->QueryDoubleAttribute("Value", &fwd_cg_limit);

    XMLElement* pAft_cg_limit = pLoading_envelope->FirstChildElement("Aft_CG_limit");
    if(pAft_cg_limit == NULL) error("Could not access Aft_CG_limit Node");
    pAft_cg_limit->QueryDoubleAttribute("Value", &aft_cg_limit);

}

// show requirements to console
ostream& operator<<(ostream& os, Requirements& r)
{
    int a {30};   // left column
    int b {11};   // right column

    os << "==============================================================================\n"
        << "Requirements\n\n"
        << setw(a) << left << "Range:"                      << setw(b) << left << r.range           << "[km]" << '\n'
        << setw(a) << left << "Payload Mass:"               << setw(b) << left << r.payload_mass    << "[kg]" << '\n'
        << setw(a) << left << "Cruise Mach Number:"         << setw(b) << left << r.cruise_mach     << "[-]" << '\n'
        << setw(a) << left << "Cruise Altitude:"            << setw(b) << left << r.cruise_alt      << "[m]" << '\n'
        << setw(a) << left << "Ultimate Load Factor:"       << setw(b) << left << r.ult_load_factor << "[-]" << '\n'
        << setw(a) << left << "Front CG limit:"             << setw(b) << left << r.fwd_cg_limit    << "[%MAC]" << '\n'
        << setw(a) << left << "Aft CG limit:"               << setw(b) << left << r.aft_cg_limit    << "[%MAC]" << '\n';

    return os;
}

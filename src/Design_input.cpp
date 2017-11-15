/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Design_input.cpp                                                                                */
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

#include "Design_input.h"
#include "vehicle/Flaps.h"
#include "std_lib_facilities.h"

#include "../TinyXML/tinyxml2.h"

using namespace std;

// reading design input file
Design_input::Design_input(const string& file_name)
{
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLNode;
    using tinyxml2::XMLElement;

    XMLDocument doc;
    doc.LoadFile(file_name.c_str());
    if(doc.Error()) error("Could not open Design File", file_name);

    XMLElement* pDesign = doc.FirstChildElement();
    if(pDesign == NULL) error("Could not access Design Node");

    // main wing

    XMLElement* pMain_wing = pDesign->FirstChildElement("Main_wing");
    if(pMain_wing == NULL) error("Could not access Main_wing Node");

    XMLElement* pFlaps = pMain_wing->FirstChildElement("Flaps");
    if(pFlaps == NULL) error("Could not access Flaps Node");

    XMLElement* pType = pFlaps->FirstChildElement("Type");
    if(pType == NULL) error("Could not access Type Node");
    Vehicle::Flaps_type type = Vehicle::string_to_flaps_type(pType->Attribute("Value"));

    XMLElement* pFlap_chord = pFlaps->FirstChildElement("Flap_chord");
    if(pFlap_chord == NULL) error("Could not access Flap_chord Node");
    double chord;
    pFlap_chord->QueryDoubleAttribute("Value", &chord);

    XMLElement* pStart_span = pFlaps->FirstChildElement("Start_span");
    if(pStart_span == NULL) error("Could not access Start_span Node");
    double start_span;
    pStart_span->QueryDoubleAttribute("Value", &start_span);

    XMLElement* pEnd_span = pFlaps->FirstChildElement("End_span");
    if(pEnd_span == NULL) error("Could not access End_span Node");
    double end_span;
    pEnd_span->QueryDoubleAttribute("Value", &end_span);


/*  // disabled as current flaps calculation lift requires no angle but flaps class still used
    // for control surfaces which are treated as flaps
    XMLElement* pDeflection_angle = pFlaps->FirstChildElement("Deflection_angle");
    if(pDeflection_angle == NULL) error("Could not access Deflection_angle Node");
    double defl_angle;
    pDeflection_angle->QueryDoubleAttribute("Value", &defl_angle);
*/
    double defl_angle = 0;  // not in use in current implementation

    main_wing_flaps = Vehicle::Flaps(type, chord, start_span, end_span, defl_angle);

    // horizontal tail

    XMLElement* pHorizontal_stabilizer = pDesign->FirstChildElement("Horizontal_stabilizer");
    if(pHorizontal_stabilizer == NULL) error("Could not access Horizontal_stabilizer Node");

    pFlaps = pHorizontal_stabilizer->FirstChildElement("Elevator");
    if(pFlaps == NULL) error("Could not access Elevator Node");

    pType = pFlaps->FirstChildElement("Type");
    if(pType == NULL) error("Could not access Type Node");
    type = Vehicle::string_to_flaps_type(pType->Attribute("Value"));

    XMLElement* pGap = pFlaps->FirstChildElement("Sealed_gap");
    if(pGap == NULL) error("Could not access Sealed_gap Node");
    bool gap;
    pGap->QueryBoolAttribute("Value", &gap);

    pFlap_chord = pFlaps->FirstChildElement("Flap_chord");
    if(pFlap_chord == NULL) error("Could not access Flap_chord Node");
    pFlap_chord->QueryDoubleAttribute("Value", &chord);

    pStart_span = pFlaps->FirstChildElement("Start_span");
    if(pStart_span == NULL) error("Could not access Start_span Node");
    pStart_span->QueryDoubleAttribute("Value", &start_span);

    pEnd_span = pFlaps->FirstChildElement("End_span");
    if(pEnd_span == NULL) error("Could not access End_span Node");
    pEnd_span->QueryDoubleAttribute("Value", &end_span);

    XMLElement* pDeflection_angle = pFlaps->FirstChildElement("Deflection_angle");
    if(pDeflection_angle == NULL) error("Could not access Deflection_angle Node");
    pDeflection_angle->QueryDoubleAttribute("Value", &defl_angle);

    elevator = Vehicle::Control_surface(Vehicle::Flaps(type, chord, start_span, end_span, defl_angle), gap);

}

// show to console
ostream& operator<<(ostream& os, Design_input& d)
{

    os << "==============================================================================\n"
        << "Design input\n\n"
        << "Main wing flaps\n"
        << d.main_wing_flaps << '\n'
        << "Horizontal stabilizer flaps\n"
        << d.elevator << '\n';

    return os;
}

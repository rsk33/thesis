/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Geom.h                                                                                          */
/* File Type:           Header-File                                                                                     */
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

#ifndef GEOM_H_INCLUDED
#define GEOM_H_INCLUDED

#include <string>
#include "../../TinyXML/tinyxml2.h"
#include "../vehicle/Aircraft.h"


namespace Vehicle {

// functions to parse vsp xml file
// first aircraft is parsed which calls wing or fuselage function
// wing and fuselage have similar parameters which are read by component parsing function

void read_geom(Vehicle::Aircraft& aircraft, const std::string& file_name);
void read_geom(Vehicle::Wing& wing, tinyxml2::XMLElement* pParmContainer);
void read_geom(Vehicle::Fuselage& fuselage, tinyxml2::XMLElement* pParmContainer);
void read_geom(Vehicle::Component& component, tinyxml2::XMLElement* pParmContainer);

}



#endif // GEOM_H_INCLUDED

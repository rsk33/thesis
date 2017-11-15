/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Initial_sizing.h                                                                                */
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

#ifndef INITIAL_SIZING_H_INCLUDED
#define INITIAL_SIZING_H_INCLUDED


#include <iostream>
#include <vector>

#include "vehicle/Component.h"

using namespace std;

// structure for in memory representation of initial sizing file
struct Initial_sizing {

    Initial_sizing(const string& file_name);

    double ref_area;          // Wing Area [m^2]
    double thrust;            // Thrust [kN]  (all engines)
    double sfc;               // SFC [(kg/h)/kN] (all engines)
    double max_take_off_mass; // Maximum Take-Off Mass [kg]
    double op_empty_mass;     // Operating Empty Mass [kg]
    double fuel_mass;         // Fuel Mass [kg]
    vector<Vehicle::Component> weight_groups;

};

// operator overload to output initial sizing to console
ostream& operator<<(ostream& os, Initial_sizing& init);

#endif // INITIAL_SIZING_H_INCLUDED

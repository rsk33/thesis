/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Requirements.h                                                                                  */
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

#ifndef Requirements_H
    #define Requirements_H

#include <iostream>

using namespace std;


//class for Requirements
struct Requirements {

    Requirements(const string& file_name);

    //Top Level Aircraft Requirements
    double range;             // Design Range [km]
    double payload_mass;      // Mass of Payload [kg]
    double cruise_mach;       // Cruise Mach number [-]
    double cruise_alt;        // Initial Cruise Altitude [m]
    double ult_load_factor;   // Ultimate Load Factor [-]
    double fwd_cg_limit;      // forward required center of gravity position limit
    double aft_cg_limit;      // aft required center of gravity position limit

};

// operator overload to output requirements to console
ostream& operator<<(ostream& os, Requirements& r);

#endif // Requirements_H

/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Aero_param.h                                                                                    */
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

#ifndef AERO_PARAM_H_INCLUDED
#define AERO_PARAM_H_INCLUDED

#include <iostream>

namespace Vsp {

// structure to represent aero parameters
struct Aero_param {
    double alpha;
    double beta;
    double roll_rate;
    double pitch_rate;
    double yaw_rate;
    double mach;
};

// helper functions

// read-in aero parameter operator overload
std::istream& operator>>(std::istream& ist, Aero_param& p);

// console output of aerodynamic parameter operator overload
std::ostream& operator<<(std::ostream& os, const Aero_param& p);

} // end of Vsp


#endif // AERO_PARAM_H_INCLUDED

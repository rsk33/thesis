/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Coef.h                                                                                          */
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

#ifndef COEF_H_INCLUDED
#define COEF_H_INCLUDED

#include <iostream>

namespace Vsp {

// structure to represent coefficients
struct Coef {
    double x_force;
    double y_force;
    double z_force;
    double x_moment;
    double y_moment;
    double z_moment;
    double lift;
    double drag;
    double slide;
    double roll_moment;
    double pitch_moment;
    double yaw_moment;
};

// helper functions

// read-in coefficients operator overload
std::istream& operator>>(std::istream& ist, Coef& c);

// operator overload to output coefficients to console
std::ostream& operator<<(std::ostream& os, const Coef& c);

} // end of Vsp

#endif // COEF_H_INCLUDED

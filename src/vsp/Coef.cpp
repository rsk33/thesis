/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Coef.cpp                                                                                        */
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

#include "Coef.h"

using namespace std;

namespace Vsp {

// operator overload to read-in aerodynamic loads coefficients
istream& operator>>(istream& ist, Coef& c)
{
    ist >> c.x_force
        >> c.y_force
        >> c.z_force
        >> c.x_moment
        >> c.y_moment
        >> c.z_moment
        >> c.lift
        >> c.drag
        >> c.slide
        >> c.roll_moment
        >> c.pitch_moment
        >> c.yaw_moment;
    return ist;
}

// operator overload to shoe aerodynamic loads coefficients to console
ostream& operator<<(ostream& os, const Coef& c)
{
    int a{13};
    os << fixed << setprecision(7)
        << setw(a) << right << c.x_force
        << setw(a) << right << c.y_force
        << setw(a) << right << c.z_force
        << setw(a) << right << c.x_moment
        << setw(a) << right << c.y_moment
        << setw(a) << right << c.z_moment
        << setw(a) << right << c.lift
        << setw(a) << right << c.drag
        << setw(a) << right << c.slide
        << setw(a) << right << c.roll_moment
        << setw(a) << right << c.pitch_moment
        << setw(a) << right << c.yaw_moment;
    return os;
}

} // end of Vsp

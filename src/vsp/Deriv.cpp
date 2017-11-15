/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Deriv.cpp                                                                                       */
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
#include <string>

#include "Deriv.h"
#include "Aero_param.h"

using namespace std;

namespace Vsp {

// operator overload to read in aerodynamic loads coefficients derivatives
istream& operator>>(istream& ist, Deriv& d)
{
    string word;
    double a;
    ist >> word >> a >> d.x_force
        >> word >> a >> d.y_force
        >> word >> a >> d.z_force
        >> word >> a >> d.x_moment
        >> word >> a >> d.y_moment
        >> word >> a >> d.z_moment
        >> word >> a >> d.lift
        >> word >> a >> d.drag
        >> word >> a >> d.slide
        >> word >> a >> d.roll_moment
        >> word >> a >> d.pitch_moment
        >> word >> a >> d.yaw_moment;
    return ist;
}

// operator overload to show aerodynamic coefficients derivatives to console
ostream& operator<<(ostream& os, const Deriv& d)
{
    os << d.x_force         << '\n'
        << d.y_force        << '\n'
        << d.z_force        << '\n'
        << d.x_moment       << '\n'
        << d.y_moment       << '\n'
        << d.z_moment       << '\n'
        << d.lift           << '\n'
        << d.drag           << '\n'
        << d.slide          << '\n'
        << d.roll_moment    << '\n'
        << d.pitch_moment   << '\n'
        << d.yaw_moment;
    return os;
}

} // end of Vsp

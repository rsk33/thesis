/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Aero_param.cpp                                                                                  */
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

#include <iomanip>
#include <iostream>

#include "Aero_param.h"

using namespace std;

namespace Vsp {

// operator overload to read-in aerodynamic parameters
istream& operator>>(istream& ist, Aero_param& p)
{
    double d; // plug for u
    ist >> p.alpha
        >> p.beta
        >> p.roll_rate
        >> p.pitch_rate
        >> p.yaw_rate
        >> p.mach
        >> d;
    return ist;
}

// operator overload to show aerodynamic parameters to console
ostream& operator<<(ostream& os, const Aero_param& p)
{
    int a{13};
    os << fixed << setprecision(7)
        << setw(a) << right << p.alpha
        << setw(a) << right << p.beta
        << setw(a) << right << p.roll_rate
        << setw(a) << right << p.pitch_rate
        << setw(a) << right << p.yaw_rate
        << setw(a) << right << p.mach;
    return os;
}

} // end of Vsp

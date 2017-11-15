/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Param.cpp                                                                                       */
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
#include <string>

#include "Param.h"

using namespace std;

namespace Vsp {

// operator overload for parameter structure read-in
istream& operator>>(istream& ist, Param& p)
{
    string word;
    ist >> word >> p.ref_area   >> word
        >> word >> p.ref_chord  >> word
        >> word >> p.ref_span   >> word
        >> word >> p.x_cg       >> word
        >> word >> p.y_cg       >> word
        >> word >> p.z_cg       >> word
        >> word >> p.mach       >> word
        >> word >> p.alpha      >> word
        >> word >> p.beta       >> word
        >> word >> p.rho        >> word
        >> word >> p.v_inf      >> word
        >> word >> p.roll_rate  >> word
        >> word >> p.pitch_rate >> word
        >> word >> p.yaw_rate   >> word;
    return ist;
}

// operator overload for parameter to console output
ostream& operator<<(ostream& os, const Param& p)
{
    int a{13};
    os << fixed << setprecision(7)
        << setw(a) << right << p.ref_area   << '\n'
        << setw(a) << right << p.ref_chord  << '\n'
        << setw(a) << right << p.ref_span   << '\n'
        << setw(a) << right << p.x_cg       << '\n'
        << setw(a) << right << p.y_cg       << '\n'
        << setw(a) << right << p.z_cg       << '\n'
        << setw(a) << right << p.mach       << '\n'
        << setw(a) << right << p.alpha      << '\n'
        << setw(a) << right << p.beta       << '\n'
        << setw(a) << right << p.rho        << '\n'
        << setw(a) << right << p.v_inf      << '\n'
        << setw(a) << right << p.roll_rate  << '\n'
        << setw(a) << right << p.pitch_rate << '\n'
        << setw(a) << right << p.yaw_rate
        << defaultfloat;
    return os;
}

} // end of Vsp

/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Lod_coef.cpp                                                                                    */
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
#include <vector>
#include <iomanip>

#include "Lod_coef.h"

using namespace std;

namespace Vsp {

// operator overload for loads file coefficients read-in
istream& operator>>(istream& ist, Lod_coef& c)
{
    ist >> c.lift
        >> c.lift_induced_drag
        >> c.slide
        >> c.x_force
        >> c.y_force
        >> c.z_force
        >> c.x_moment
        >> c.y_moment
        >> c.z_moment;
    return ist;
}

// operator overload to output lad file coefficients to console
ostream& operator<<(ostream& os, const Lod_coef& c)
{
    int a{13};
    os  << setw(a) << right << c.lift
        << setw(a) << right << c.lift_induced_drag
        << setw(a) << right << c.slide
        << setw(a) << right << c.x_force
        << setw(a) << right << c.y_force
        << setw(a) << right << c.z_force
        << setw(a) << right << c.x_moment
        << setw(a) << right << c.y_moment
        << setw(a) << right << c.z_moment;
    return os;
}

} // end of Vsp

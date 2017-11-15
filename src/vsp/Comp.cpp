/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Comp.cpp                                                                                        */
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

#include "Comp.h"

using namespace std;

namespace Vsp {

// operator overload to read component coefficients
istream& operator>>(istream& ist, Comp& l)
{
    double blank;

    ist >> blank
        >> l.name
        >> blank
        >> blank
        >> blank
        >> l.coef;

    return ist;
}

// operator overload to show component coefficients to console
ostream& operator<<(ostream& os, const Comp& c)
{
    int a{13};
    os << setw(a) << right << c.name
        << fixed << setprecision(5)
        << setw(a) << right << c.coef
        << defaultfloat;

    return os;
}

} // end of Vsp

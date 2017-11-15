/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Component.cpp                                                                                   */
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

#include "Component.h"
#include "Coord_sys.h"

using namespace std;

namespace Vehicle {

ostream& operator<<(ostream& os, const Component& c)
{
    int l {25};   // left column
    int r {11};   // right column

    os  << setw(l) << left << "ID ="            << setw(r) << left << c.id() << '\n'
      //  << setw(l) << left << "Location:"       << '\n' << c.loc() << '\n'
       // << setw(l) << left << "Rotation:"       << '\n' << c.rot() << '\n'
      //  << setw(l) << left << "XZ Symmetry ="   << setw(r) << left << boolalpha << c.symm_xz() << '\n'
        << setw(l) << left << "Mass ="          << setw(r) << left << c.mass() << '\n'
        << setw(l) << left << "CG location:"    << '\n' << c.cg();

    return os;
}

}

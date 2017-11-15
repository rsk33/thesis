/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Coord_sys.cpp                                                                                   */
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

#include "Coord_sys.h"


using namespace std;

namespace Vehicle {

ostream& operator<<(ostream& os, const Coord_sys& c)
{
    int l {25};   // left column
    int r {11};   // right column

    os  << setw(l) << left << "X-Coordinate =" << setw(r) << left << c.x() << "[m]" << '\n'
        << setw(l) << left << "Y-Coordinate =" << setw(r) << left << c.y() << "[m]" << '\n'
        << setw(l) << left << "Z-Coordinate =" << setw(r) << left << c.z() << "[m]";

    return os;
}

}

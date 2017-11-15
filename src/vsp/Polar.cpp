/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Polar.cpp                                                                                       */
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
#include <vector>
#include <string>

#include "Polar.h"

using namespace std;

namespace Vsp {

// operator overload to read a polar individual entry
istream& operator>>(istream& is, Polar& p)
{
    is >> p.beta
        >> p.mach
        >> p.alpha
        >> p.lift
        >> p.zero_lift_drag
        >> p.lift_induced_drag
        >> p.drag
        >> p.slide
        >> p.lift_to_drag
        >> p.oswald
        >> p.x_force
        >> p.y_force
        >> p.z_force
        >> p.x_moment
        >> p.y_moment
        >> p.z_moment
        >> p.roll_moment
        >> p.pitch_moment
        >> p.yaw_moment;
    return is;
}

// operator overload for polar to console output
ostream& operator<<(ostream& os, const Polar& p)
{
    int l{10};
    os << fixed << setprecision(5)
        << setw(l) << right << p.beta
        << setw(l) << right << p.mach
        << setw(l) << right << p.alpha
        << setw(l) << right << p.lift
        << setw(l) << right << p.zero_lift_drag
        << setw(l) << right << p.lift_induced_drag
        << setw(l) << right << p.drag
        << setw(l) << right << p.slide
        << setw(l) << right << p.lift_to_drag
        << setw(l) << right << p.oswald
        << setw(l) << right << p.x_force
        << setw(l) << right << p.y_force
        << setw(l) << right << p.z_force
        << setw(l) << right << p.x_moment
        << setw(l) << right << p.y_moment
        << setw(l) << right << p.z_moment
        << setw(l) << right << p.roll_moment
        << setw(l) << right << p.pitch_moment
        << setw(l) << right << p.yaw_moment;
    return os;
}

// function reads a vspaero polar file into polar data type container
void fill_vector(istream& ist, vector<Polar>& v)
{
    string line;
    getline(ist,line);             // skip a header line

    // read all individual entries
    for(Polar p; ist >> p;){
        v.push_back(p);
    }

}


} // end of Vsp

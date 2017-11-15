/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Flaps.cpp                                                                                       */
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
#include <cmath>
#include "Flaps.h"

using namespace std;

namespace Vehicle {

double Flaps::delta_aoa_zero_lift() const
{
    // Raymer
    double delta = ( 1.579 * pow(m_chord, 3) - 3.458 * pow(m_chord, 2) + 2.882 * m_chord ) * ( m_angle);

    return delta;
}

double Flaps::delta_max_airfoil_lift_coef() const
{
    // Raymer
    if(m_type == Flaps_type::plain)
        return 0.9;
    else if(m_type == Flaps_type::slotted)
        return 1.3;
    else
        return 0; // not defined
}




string flaps_type_to_string(Flaps_type f)
{
    switch (f) {
    case Flaps_type::plain:
        return "Plain";
    case Flaps_type::slotted:
        return "Slotted";

    default:
        throw invalid_argument("flaps_type");
    }
}

Flaps_type string_to_flaps_type(const string& flaps_type)
{
    if(flaps_type == "Plain")
        return Flaps_type::plain;
    else if(flaps_type == "Slotted")
        return Flaps_type::slotted;

    else{
        throw invalid_argument("flaps_type");
    }
}

ostream& operator<<(ostream& os, Flaps& f)
{
    int a {30};   // left column
    int b {11};   // right column
    os  << setw(a) << left << "Type: " << setw(b) << left << flaps_type_to_string(f.type()) << '\n'
        << setw(a) << left << "Chord: " << setw(b) << left << f.chord() << '\n'
        << setw(a) << left << "Span start: " << setw(b) << left << f.span_start() << '\n'
        << setw(a) << left << "Span end: " << setw(b) << left << f.span_end() << '\n'
        << setw(a) << left << "Angle: " << setw(b) << left << f.angle() << "[DEG]" << '\n';

    return os;
}

}

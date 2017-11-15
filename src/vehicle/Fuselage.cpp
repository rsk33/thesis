/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Fuselage.cpp                                                                                    */
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


#include "Fuselage.h"
#include "Component.h"
#include "Coord_sys.h"

using namespace std;

namespace Vehicle {

Fuselage::Fuselage(const Component& component, double length, double diam)
    : Aero_component{component},
    m_length{length},
    m_diam{diam}
    {
    }


Coord_sys Fuselage::cg() const
{
    double x = loc().x() + m_length * 0.39;
    return Coord_sys {x, loc().y(), loc().z()};
}

double Fuselage::fineness() const
{
    return m_length / m_diam;
}

ostream& operator<<(ostream& os, const Fuselage& f)
{
    int l {25};   // left column
    int r {11};   // right column

    os  << setw(l) << left << "ID ="            << setw(r) << left << f.id() << '\n'
        << setw(l) << left << "Location:"       << '\n' << f.loc() << '\n'
        << setw(l) << left << "Length ="        << setw(r) << left << f.length()        << "[m]" << '\n'
        << setw(l) << left << "Diameter ="      << setw(r) << left << f.diam()          << "[m]" << '\n'
        << setw(l) << left << "Fineness ratio ="  << setw(r) << left << f.fineness()    << "[-]" << '\n'
        << setw(l) << left << "Properties:"     << '\n'
        << setw(l) << left << "Mass ="          << setw(r) << left << f.mass()          << "[kg]" << '\n'
        << setw(l) << left << "CG:"             << '\n' << f.cg() << '\n'
        << setw(l) << left << "Wet area ="      << setw(r) << left << f.wet_area()      << "[m^2]" << '\n'
        << setw(l) << left << "CD0 =" << setw(r) << left << f.zero_lift_drag() << "[-]";

    return os;
}

}

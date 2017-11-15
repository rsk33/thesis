/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Wing.cpp                                                                                        */
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
#include <math.h>


#include "Wing.h"
#include "Coord_sys.h"
#include "Component.h"
#include "Aero_component.h"
#include "../std_lib_facilities.h"


using namespace std;

namespace Vehicle {


Wing::Wing(const Component& component, double area, double span,
            double aspect, double taper, double tip_chord, double tip_thick,
            double root_chord, double root_thick,
            double sweep, double sweep_loc,
            double twist, double twist_loc, double dihedral)
    : Aero_component{component},
    m_area{area},
    m_span{span},
    m_aspect{aspect},
    m_taper{taper},
    m_tip_chord{tip_chord},
    m_tip_thick{tip_thick},
    m_root_chord{root_chord},
    m_root_thick{root_thick},
    m_sweep{sweep},
    m_sweep_loc{sweep_loc},
    m_twist{twist},
    m_twist_loc{twist_loc},
    m_dihedral{dihedral}
    {
    }

double Wing::area() const
{
    if(symm_xz())
        return m_area * 2;
    else
        return m_area;
}

double Wing::span() const
{
    if(symm_xz())
        return m_span * 2;
    else
        return m_span;
}

double Wing::aspect() const
{
    if(symm_xz())
        return m_aspect * 2;
    else
        return m_aspect;
}

// function returns sweep angle in degrees
// argument is chordwise location of the sweep line. 0 - leading edge, 1 - trailing edge
double Wing::sweep(double location) const
{
    double l_sweep = atan ( tan( m_sweep * PI / 180 ) -
                    ( 4 / ( 2 * m_aspect ) ) * ( location - m_sweep_loc ) *
                    ( 1 - m_taper ) / ( 1 + m_taper ) ) * 180 / PI;

    return l_sweep;
}

double Wing::mean_geom_chord() const
{
    double mgc = ( 2.0 / 3 ) * m_root_chord *
                ( 1 + m_taper + pow( m_taper, 2 ) ) / ( 1 + m_taper ) ;
    return mgc;
}


double Wing::mean_geom_chord_x() const
{
    return mean_geom_chord_y() * tan( sweep(0) * PI / 180 );
}

double Wing::mean_geom_chord_y() const
{
    return ( m_span / 3 ) * ( ( 1 + 2 * m_taper ) / ( 1 + m_taper ) );
}

double Wing::aerod_center_loc_x() const
{
    return loc().x() + mean_geom_chord_x() + mean_geom_chord() * 0.25;
}



double Wing::chord_le_edge_loc_x(double half_span_dist_frac) const
{
    return half_span_dist_frac * m_span * tan(sweep(0) * PI / 180);
}

// function returns chord length for the half span
double Wing::chord_length(double half_span_dist_frac) const
{
    double length = m_root_chord + half_span_dist_frac * m_span *
                    (tan(sweep(1) * PI / 180) - tan(sweep(0) * PI / 180));
    return length;
}

Coord_sys Wing::cg() const
{
    double x = loc().x() + chord_le_edge_loc_x(0.35) + 0.465 * chord_length(0.35);

    return Coord_sys {x, loc().y(), loc().z()};
}

ostream& operator<<(ostream& os, const Wing& w)
{
    int l {25};   // left column
    int r {11};   // right column

    os  << setw(l) << left << "ID ="                    << setw(r) << left << w.id() << '\n'
        << setw(l) << left << "Geometry:"               << '\n'
        << setw(l) << left << "Location:"               << '\n' << w.loc() << '\n'
        << setw(l) << left << "XZ Symmetry ="           << setw(r) << left << boolalpha << w.symm_xz()  << '\n'
        << setw(l) << left << "Area ="                  << setw(r) << left << w.area()              << "[m^2]" << '\n'
        << setw(l) << left << "Span ="                  << setw(r) << left << w.span()              << "[m]" << '\n'
        << setw(l) << left << "Aspect ="                << setw(r) << left << w.aspect()            << "[-]" << '\n'
        << setw(l) << left << "Taper ="                 << setw(r) << left << w.taper()             << "[-]" << '\n'
        << setw(l) << left << "Tip chord ="             << setw(r) << left << w.tip_chord()         << "[m]" << '\n'
        << setw(l) << left << "Tip thickness ="         << setw(r) << left << w.tip_thick()         << "[%]" << '\n'
        << setw(l) << left << "Root chord ="            << setw(r) << left << w.root_chord()        << "[m]" << '\n'
        << setw(l) << left << "Root thickness ="        << setw(r) << left << w.root_thick()        << "[%]" << '\n'
        << setw(l) << left << "Mean geometric chord ="  << setw(r) << left << w.mean_geom_chord()   << "[m]" << '\n'
        << setw(l) << left << "Sweep at 1/4 chord ="    << setw(r) << left << w.sweep(0.25)         << "[DEG]" << '\n'
        << setw(l) << left << "Twist ="                 << setw(r) << left << w.twist()             << "[DEG]" << '\n'
        << setw(l) << left << "Twist location ="        << setw(r) << left << w.twist_loc()         << "[%]" << '\n'
        << setw(l) << left << "Dihedral ="              << setw(r) << left << w.dihedral()          << "[DEG]" << '\n'
        << setw(l) << left << "Properties:"             << '\n'
        << setw(l) << left << "Mass ="                  << setw(r) << left << w.mass()              << "[kg]" << '\n'
        << setw(l) << left << "CG:"                     << '\n' << w.cg() << '\n'
        << setw(l) << left << "Wet area ="              << setw(r) << left << w.wet_area()          << "[m^2]" << '\n'
        << setw(l) << left << "Aero. center loc. ="     << setw(r) << left << w.aerod_center_loc_x() << "[m]" << '\n'
        << setw(l) << left << "CD0 ="                   << setw(r) << left << w.zero_lift_drag()    << "[-]";

    return os;
}

}

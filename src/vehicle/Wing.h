/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Wing.h                                                                                          */
/* File Type:           Header-File                                                                                     */
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

#ifndef WING_H_INCLUDED
#define WING_H_INCLUDED

#include <iostream>

#include "Component.h"
#include "Aero_component.h"
#include "Coord_sys.h"
#include "Flaps.h"

namespace Vehicle {

class Wing : public Aero_component {
public:
    Wing() {}
    Wing(const Component& component, double area, double span,
            double aspect, double taper, double tip_chord, double tip_thick,
            double root_chord, double root_thick,
            double sweep, double sweep_loc,
            double twist, double twist_loc, double dihedral);

    double area() const;
    double span() const;
    double aspect() const;
    double taper() const { return m_taper; }
    double tip_chord() const { return m_tip_chord; }
    double tip_thick() const { return m_tip_thick; }
    double root_chord() const { return m_root_chord; }
    double root_thick() const { return m_root_thick; }
    double av_thick() const { return ( m_root_thick + m_tip_thick ) / 2; }
    double twist() const { return m_twist; }
    double twist_loc() const { return m_twist_loc; }
    double dihedral() const { return m_dihedral; }

    double sweep(double location) const;
    double mean_geom_chord() const;
    double aerod_center_loc_x() const;
    double chord_le_edge_loc_x(double half_span_dist_frac) const;
    double chord_length(double half_span_dist_frac) const;

    Coord_sys cg() const;


private:
    double m_area{};
    double m_span{};
    double m_aspect{};
    double m_taper{};
    double m_tip_chord{};
    double m_tip_thick{};
    double m_root_chord{};
    double m_root_thick{};
    double m_sweep{};
    double m_sweep_loc{};
    double m_twist{};
    double m_twist_loc{};
    double m_dihedral{};
    Flaps m_flaps{};

    // mean geometrical chord leading edge location coordinates
    double mean_geom_chord_x() const;
    double mean_geom_chord_y() const;


};

std::ostream& operator<<(std::ostream& os, const Wing& w);


// determine main wing which is assumed to have biggest area
static bool compare_area(const Wing& a, const Wing& b)
{
    return (a.area() < b.area());
}


// determine vertical tail which is 90 DEG rotated with respect to X-axis
static bool vertical(const Wing& a)
{
    return (a.rot().x() == 90); // 90 DEG rotation around X-axis
}

}

#endif // WING_H_INCLUDED

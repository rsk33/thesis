/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Component.h                                                                                     */
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

#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#include <string>
#include <iostream>

#include "Coord_sys.h"

namespace Vehicle {

class Component {
public:
    Component() {}
    Component(const std::string& id, const Coord_sys& loc = {},
              const Coord_sys& rot = {}, bool symm_xz = false)
        : m_id{id},
        m_loc{loc},
        m_rot{rot},
        m_symm_xz{symm_xz}
        {
        }

    // non-modifying member functions
    std::string id() const { return m_id; }
    Coord_sys loc() const { return m_loc; }
    Coord_sys rot() const { return m_rot; }
    bool symm_xz() const { return m_symm_xz; }
    double mass() const { return m_mass; }
    virtual Coord_sys cg() const { return m_cg; }

    // modifying member functions
    void set_mass(double value) { m_mass = value; }
    void set_cg(Coord_sys cg) { m_cg = cg; }

private:
    std::string m_id;
    Coord_sys m_loc;
    Coord_sys m_rot;
    bool m_symm_xz{};
    double m_mass{};
    Coord_sys m_cg;
};

std::ostream& operator<<(std::ostream& os, const Component& c);

}

#endif // COMPONENT_H_INCLUDED

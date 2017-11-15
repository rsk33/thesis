/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Aircraft.h                                                                                      */
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

#ifndef AIRCRAFT_H_INCLUDED
#define AIRCRAFT_H_INCLUDED

#include <iostream>
#include <vector>

#include "Fuselage.h"
#include "Wing.h"
#include "Horizontal_tail.h"
#include "Vertical_tail.h"
#include "Aero_component.h"
#include "../Initial_sizing.h"
#include "../Requirements.h"
#include "../Design_input.h"

namespace Vehicle {

class Aircraft : public Aero_component {

public:
    Aircraft(){}
    Aircraft(const Requirements& req, const Initial_sizing& init, const Design_input& des_inp);

    // modifying functions
    void set_oswald(double val) { m_oswald = val; }
    void set_mass_operating_empty(double val) { m_mass_operating_empty = val; }
    // components
    Fuselage& fuselage() { return m_fuselage; }
    Wing& main_wing() { return m_main_wing; }
    Horizontal_tail& horiz_tail() { return m_horiz_tail; }
    Vertical_tail& vert_tail() { return m_vert_tail; }

    // non-modifying functions
    std::vector<Component> weight_groups() const { return m_weight_groups; }
    // flaps
    Flaps main_wing_flaps() const { return m_main_wing_flaps; }
    double main_wing_aerod_center_flaps() const;
    double delta_max_lift_coef_flaps() const;
    // elevator
    Control_surface elevator() const { return m_elevator; }
    // cruise param
    double cruise_mach() const { return m_cruise_mach; }
    double cruise_speed() const;
    double cruise_alt() const { return m_cruise_alt; }
    // powerplant
    double sfc() const { return m_sfc; }
    double thrust() const { return m_thrust; }
    // mass
    double mass_fuel() const;
    double mass_payload() const { return m_mass_payload; }
    double mass_operating_empty() const { return m_mass_operating_empty; }
    double mass_max_take_off() const { return m_mass_max_take_off; }
    // double mass_max_take_off() const { return m_mass_fuel + m_mass_payload + m_mass_operating_empty; }
    double mass_gross() const;
    Coord_sys cg() const;
    double aft_cg_limit() const { return m_aft_cg_limit; }
    double fwd_cg_limit() const { return m_fwd_cg_limit; }
    double ult_load_factor() const { return m_ult_load_factor; }
    // aero param
    double lift_coef_cruise() const;
    double lift_induced_drag_cruise() const;
    double lift_induced_drag(double lift_coef) const;
    double total_drag_coef(double lift_coef) const;
    double total_drag_coef_cruise() const;
    double lift_to_drag_cruise() const;
    double oswald() const { return m_oswald; }

    double range() const;
    double horiz_tail_lever() const;
    double ref_area() const { return m_main_wing.area(); }

private:
    Fuselage m_fuselage;
    Wing m_main_wing;
    Horizontal_tail m_horiz_tail;
    Vertical_tail m_vert_tail;

    Flaps m_main_wing_flaps;
    Control_surface m_elevator;

    std::vector<Component> m_weight_groups;

    double m_cruise_mach {};
    double m_cruise_alt {};
    double m_sfc {};
    double m_thrust {};
    double m_mass_fuel {};
    double m_mass_payload {};
    double m_mass_operating_empty {};
    double m_mass_max_take_off {};
    double m_ult_load_factor {};
    double m_fwd_cg_limit {};
    double m_aft_cg_limit {};
    double m_oswald {};

};

std::ostream& operator<<(std::ostream& os, Aircraft& c);

}

#endif // AIRCRAFT_H_INCLUDED

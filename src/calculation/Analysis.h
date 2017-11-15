/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Analysis.h                                                                                      */
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

#ifndef ANALYSIS_H_INCLUDED
#define ANALYSIS_H_INCLUDED

#include <iostream>

#include "Method.h"
#include "../vehicle/Aircraft.h"
#include "../control/Settings.h"
#include "Results.h"

namespace Calculation {

// Analysis class is used to organize different types and methods of calculations and algorithms
class Analysis {

public:
    Analysis(const Control::Settings& settings, const Requirements& requirements,
            const Initial_sizing& initial_sizing);

    // analysis member functions
    void wet_area(Vehicle::Aircraft& aircraft) const;
    void mass(Vehicle::Aircraft& aircraft) const;
    void zero_lift_drag(Vehicle::Aircraft& aircraft) const;
    void lift_induced_drag(Vehicle::Aircraft& aircraft) const;
    void design_to_range(Vehicle::Aircraft& aircraft);
    void horiz_stab_sizing(Vehicle::Aircraft& aircraft);

    // results - used for output
    Results results() const { return m_results; }

private:
    Control::Settings m_settings;   // to store configuration of calculations
    Results m_results;  // to store results of calculations

    // wet area calculation using vsp function
    void wet_area_vsp(Vehicle::Aircraft& aircraft) const;

    // mass calculation functions
    void torenbeek_mass_second_class_fuselage(Vehicle::Aircraft& aircraft) const;
    void torenbeek_mass_second_class_main_wing(Vehicle::Aircraft& aircraft) const;
    void torenbeek_mass_second_class_horiz_tail(Vehicle::Aircraft& aircraft) const;
    void torenbeek_mass_second_class_vert_tail(Vehicle::Aircraft& aircraft) const;

    // drag calculation functions
    void zero_lift_drag_raymer(Vehicle::Fuselage& fuselage, double cruise_alt,
                              double cruise_mach, double ref_area) const;
    void zero_lift_drag_raymer(Vehicle::Wing& wing, double cruise_alt,
                              double cruise_mach, double ref_area) const;

    double skin_friction(double characteristic_length, double mach, double alt) const;

    void lift_induced_drag_douglas(Vehicle::Aircraft& aircraft) const;
    void lift_induced_drag_vsp_aero_vlm(Vehicle::Aircraft& aircraft) const;
    void lift_induced_drag_vsp_aero_panel(Vehicle::Aircraft& aircraft) const;

    // horizontal stabilizer sizing functions
    bool vsp_horiz_stab_sizing(Vehicle::Aircraft& aircraft);
    void cg_limits(Vehicle::Aircraft& aircraft, double stab_to_wing_ratio,
                         double& fwd_limit, double& aft_limit) const;

};

}   // Calculation

#endif // ANALYSIS_H_INCLUDED

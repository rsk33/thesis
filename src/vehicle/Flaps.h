/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Flaps.h                                                                                         */
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

#ifndef FLAPS_H_INCLUDED
#define FLAPS_H_INCLUDED

#include <iostream>


namespace Vehicle {

enum class Flaps_type {

    plain,
    slotted
};


class Flaps {
public:
    Flaps() {}
    Flaps(Flaps_type type, double chord, double span_start, double span_end, double angle)
        : m_type{type}, m_chord{chord}, m_span_start{span_start}, m_span_end{span_end}, m_angle{angle} {}

    Flaps_type type() const { return m_type; }
    double chord() const { return m_chord; }
    double span_start() const { return m_span_start; }
    double span_end() const { return m_span_end; }
    double angle() const { return m_angle; }
    double delta_aoa_zero_lift() const;
    double delta_max_airfoil_lift_coef() const;


private:

    Flaps_type m_type;
    double m_chord;
    double m_span_start;
    double m_span_end;
    double m_angle; // deflection angle


};

std::string flaps_type_to_string(Flaps_type f);

Flaps_type string_to_flaps_type(const std::string& flaps_type);

std::ostream& operator<<(std::ostream& os, Flaps& f);

}

#endif // FLAPS_H_INCLUDED

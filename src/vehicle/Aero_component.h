/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Aero_component.h                                                                                */
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

#ifndef AERO_COMPONENT_H_INCLUDED
#define AERO_COMPONENT_H_INCLUDED

#include "Component.h"

namespace Vehicle {


class Aero_component : public Component {
public:
    Aero_component() {}
    Aero_component(const Component& component)
        : Component{component} {}

    double wet_area() const { return m_wet_area; }
    double zero_lift_drag() const { return m_zero_lift_drag; }

    void set_wet_area(double value) { m_wet_area = value; }
    void set_zero_lift_drag(double value) { m_zero_lift_drag = value; }

private:
    double m_wet_area{};
    double m_zero_lift_drag{};

};

}



#endif // AERO_COMPONENT_H_INCLUDED

/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Deriv.h                                                                                         */
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

#ifndef DERIV_H_INCLUDED
#define DERIV_H_INCLUDED

#include <iostream>

#include "Aero_param.h"

namespace Vsp {

// structure to represent aerodynamic loads coefficients derivatives with aerodynamic parameters
struct Deriv {
    Aero_param x_force;
    Aero_param y_force;
    Aero_param z_force;
    Aero_param x_moment;
    Aero_param y_moment;
    Aero_param z_moment;
    Aero_param lift;
    Aero_param drag;
    Aero_param slide;
    Aero_param roll_moment;
    Aero_param pitch_moment;
    Aero_param yaw_moment;
};

// helper functions

std::istream& operator>>(std::istream& ist, Deriv& d);

std::ostream& operator<<(std::ostream& os, const Deriv& d);

} // end of Vsp

#endif // DERIV_H_INCLUDED

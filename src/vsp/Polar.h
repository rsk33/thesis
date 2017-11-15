/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Polar.h                                                                                         */
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

#ifndef POLAR_H_INCLUDED
#define POLAR_H_INCLUDED

#include <iostream>
#include <vector>

#include "Aero_param.h"
#include "Coef.h"

namespace Vsp {


// structure to represent an individual entry of a polar output file of vspaero
struct Polar : Aero_param , Coef {
    double zero_lift_drag;
    double lift_induced_drag;
    double lift_to_drag;
    double oswald;
};

// helper functions

std::istream& operator>>(std::istream& is, Polar& p);

std::ostream& operator<<(std::ostream& os, const Polar& p);

// read file into polar data type container
void fill_vector(std::istream& ist, std::vector<Polar>& v);



} // end of Vsp

#endif // POLAR_H_INCLUDED

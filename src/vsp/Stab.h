/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Stab.h                                                                                          */
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

#ifndef STAB_H_INCLUDED
#define STAB_H_INCLUDED


#include <vector>
#include <fstream>

#include "Param.h"
#include "Coef.h"
#include "Deriv.h"

namespace Vsp {

// structure used to represent an individual entry of the vspaero stability output file
struct Stab {
    Param param;
    Coef coef;
    Deriv deriv;
};

// helper functions

std::istream& operator>>(std::istream& ist, Stab& s);

std::ostream& operator<<(std::ostream& os, const Stab& s);

// function reads vspaero stability output file into container of Stab data type
void fill_vector(std::istream& ist, std::vector<Stab>& s);

} // end of Vsp

#endif // STAB_H_INCLUDED

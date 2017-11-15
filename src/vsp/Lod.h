/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Lod.h                                                                                           */
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

#ifndef LOD_H_INCLUDED
#define LOD_H_INCLUDED

#include <vector>
#include <fstream>

#include "Param.h"
#include "Comp.h"
#include "Lod_coef.h"


namespace Vsp {

// structure to represent an individual entry of a loads file
struct Lod {
    Param param;
    std::vector<Comp> comps;
};

// helper function

std::istream& operator>>(std::istream& ist, Lod& l);

std::ostream& operator<<(std::ostream& os, const Lod& l);

// read vspaero loads output file into loads data type container
void fill_vector(std::istream& ist, std::vector<Lod>& l);


} // end of Vsp


#endif // LOD_H_INCLUDED

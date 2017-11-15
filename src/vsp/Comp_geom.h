/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Comp_geom.h                                                                                     */
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

#ifndef COMP_GEOM_H_INCLUDED
#define COMP_GEOM_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>


namespace Vsp {

//===============================================================================================
//=== class Comp_geom ===//

// class and functions to read in csv file and save structured data
// from OpenVSP CompGeom analysis report
// class for in-memory representation of computed component values
// name, theoretical area, wetted area, theoretical volume and wetted volume
// wetted - trimmed, theoretical untrimmed

struct Comp_geom {
    std::string name;
    double theor_area;
    double wett_area;
    double theor_vol;
    double wett_vol;
};
//--- class Comp_geom helper functions ---//


// input operator overload. read string and create Comp_geom instance
std::istream& operator>>(std::istream& is, Comp_geom& comp);

// output operator overload
std::ostream& operator<<(std::ostream& os, Comp_geom& comp);

// function reads vsp compgeom csv file into container of Comp_geom data type,
// each component has it's individual entry
void fill_vector(std::istream& ist, std::vector<Comp_geom>& v);

} // end of Vsp

#endif // COMP_GEOM_H_INCLUDED

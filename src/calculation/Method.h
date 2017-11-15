/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Method.h                                                                                        */
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

#ifndef METHOD_H_INCLUDED
#define METHOD_H_INCLUDED

#include <string>

namespace Calculation {

// enumerator used to list possible methods
enum class Method{

    none,
    hand_book,
    kundu_1,
    raymer_1,
    kundu_2,
    torenbeek_2,
    drag_build_up_raymer,
    douglas,
    vsp,
    vsp_aero,
    vsp_aero_vlm,
    vsp_aero_panel,

};

// helper functions

// function converts Method enumerator value to string
std::string method_to_string(Method m);

// function converts method string to enum value
Method string_to_method(const std::string& method);

}   // Calculation

#endif // METHOD_H_INCLUDED

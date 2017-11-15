/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Method.cpp                                                                                      */
/* File Type:           Source-File                                                                                     */
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

#include <string>
#include <stdexcept>

#include "Method.h"

using namespace std;

namespace Calculation {

// function converts Method enum value to string
string method_to_string(Method m)
{
    switch (m) {
    case Method::none:
        return "none";
    case Method::hand_book:
        return "Hand Book";
    case Method::kundu_1:
        return "Kundu I Class";
    case Method::raymer_1:
        return "Raymer I Class";
    case Method::kundu_2:
        return "Kundu II Class";
    case Method::torenbeek_2:
        return "Torenbeek II Class";
    case Method::drag_build_up_raymer:
        return "Drag Build-up Raymer";
    case Method::douglas:
        return "Douglas";
    case Method::vsp_aero:
        return "VSPAERO Analysis";
    case Method::vsp:
        return "OpenVSP";
    case Method::vsp_aero_vlm:
        return "VSPAERO VLM";
    case Method::vsp_aero_panel:
        return "VSPAERO Panel";
    default:
        throw invalid_argument("method");   // error reporting
    }
}

// function converts method string to enum value
Method string_to_method(const string& method)
{
    if(method == "none")
        return Method::none;
    else if(method == "hand_book")
        return Method::hand_book;
    else if(method == "kundu_1")
        return Method::kundu_1;
    else if(method == "raymer_1")
        return Method::raymer_1;
    else if(method == "kundu_2")
        return Method::kundu_2;
    else if(method == "torenbeek_2")
        return Method::torenbeek_2;
    else if(method == "drag_build_up_raymer")
        return Method::drag_build_up_raymer;
    else if(method == "douglas")
        return Method::douglas;
    else if(method == "vsp_aero")
        return Method::vsp_aero;
    else if(method == "vsp")
        return Method::vsp;
    else if(method == "vsp_aero_vlm")
        return Method::vsp_aero_vlm;
    else if(method == "vsp_aero_panel")
        return Method::vsp_aero_panel;
    else{
        throw invalid_argument("method");   // error reporting
    }
}

}   // Calculation

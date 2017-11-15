/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Settings.h                                                                                      */
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

#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include <iostream>
#include <string>

#include "Settings.h"
#include "Variable.h"
#include "Criterion.h"
#include "File_type.h"
#include "../calculation/Method.h"

namespace Control {

//===============================================================================================
//=== class Settings ===//

// class Settings for general and project specific settings representation
struct Settings {

    // constructor
    Settings(const std::string& file_name);

    // function returns file relative address and name for certain file type
    std::string file_name(const File_type& file_fype) const;    // returns files full name for a file type
    void delete_temp_files() const; // deletes temporary files

    // general settings
    std::string project_name;
    std::string vsp_dir;
    int vspaero_threads;
    int vspaero_wakes;
    double vspaero_mach;

    // project specific settings
    Variable variable;
    Criterion criterion;
    Calculation::Method wet_area;
    Calculation::Method mass;
    Calculation::Method zero_lift_drag;
    Calculation::Method lift_induced_drag;
    Calculation::Method trim;
    double trim_angle_of_attack;
    Calculation::Method static_stability;
    double static_stability_margin;

};

std::ostream& operator<<(std::ostream& os, Settings& s);

}   // end of Control

#endif // SETTINGS_H_INCLUDED

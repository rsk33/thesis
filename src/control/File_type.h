/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Fie_type.h                                                                                      */
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

#ifndef FILE_TYPE_H_INCLUDED
#define FILE_TYPE_H_INCLUDED


namespace Control {

// type of files
enum class File_type
{
    settings,                                   // project specific settings file in input directory
    requirements,                               // requirements input file in input directory
    initial_sizing,                             // initial sizing input file in input directory
    design_input,                               // design input file in input directory
    outp_dir,                                   // output directory
    gaf,                                        // general aircraft file in output directory
    vsp,                                        // vsp input model in input directory
    vsp_new,                                    // copy of vsp input file in output directory
    main_wing_and_ht_only,                      // reduced vsp model in output directory
    comp_geom_csv,                              // vsp comp geom file in output directory
    comp_geom_txt,                              // vsp comp geom file in output directory
    degen_geom,                                 // vsp degen geom file (required for VLM) in output directory
    degen_geom_csv,                             // vsp degen geom file in output directory
    main_wing_and_ht_only_degen_geom_csv,       // vsp degen geom file of reduced model in output directory
    vspaero_vspaero,                            // vspaero setup file in output directory
    vspaero_polar,                              // vspaero polar file in output directory
    vspaero_stab,                               // vspaero stab file in output director
    vspaero_adb,                                // vspaero adb file in output directory
    vspaero_adb_cases,                          // vspaero adb cases file in output directory
    vspaero_fem,                                // vspaero fem file in output directory
    vspaero_history,                            // vspaero history file in output directory
    vspaero_lod,                                // vspaero loads file in output directory
    tri,                                        // triangulated surface file (required for Panel method) in output directory
    main_wing_and_ht_only_vspaero_vspaero,      // reduced model files in output directory --//--
    main_wing_and_ht_only_vspaero_polar,
    main_wing_and_ht_only_vspaero_stab,
    main_wing_and_ht_only_vspaero_adb,
    main_wing_and_ht_only_vspaero_adb_cases,
    main_wing_and_ht_only_vspaero_fem,
    main_wing_and_ht_only_vspaero_history,
    main_wing_and_ht_only_vspaero_lod,

};

}   // end of Control

#endif // FILE_TYPE_H_INCLUDED

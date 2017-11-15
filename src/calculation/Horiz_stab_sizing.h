/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Horiz_stab_sizing.h                                                                             */
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

#ifndef HORIZ_STAB_SIZING_H_INCLUDED
#define HORIZ_STAB_SIZING_H_INCLUDED

namespace Calculation {

// structure used to report horizontal stabilizer sizing parameters
struct Horiz_stab_sizing {

    double wing_pos;
    double main_wing_aerod_center_pos;
    double main_wing_mean_geom_chord;
    double cg_pos;
    double horiz_tail_aerod_center_pos;
    double small_stab_area_ratio;
    double big_stab_area_ratio;
    double small_stab_fwd_cg_limit;
    double small_stab_aft_cg_limit;
    double big_stab_fwd_cg_limit;
    double big_stab_aft_cg_limit;
    double trim_req_stab_area_ratio;
    double static_stab_req_stab_area_ratio;

};

}   // Calculation

#endif // HORIZ_STAB_SIZING_H_INCLUDED

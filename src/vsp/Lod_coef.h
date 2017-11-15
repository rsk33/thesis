/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Lod_coef.h                                                                                      */
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

#ifndef LOD_COEF_H_INCLUDED
#define LOD_COEF_H_INCLUDED


namespace Vsp {

// structure to represent aerodynamic loads coefficients of loads vspaero output file
struct Lod_coef {
    double lift;
    double lift_induced_drag;
    double slide;
    double x_force;
    double y_force;
    double z_force;
    double x_moment;
    double y_moment;
    double z_moment;
};

// helper functions

std::istream& operator>>(std::istream& ist, Lod_coef& l);

std::ostream& operator<<(std::ostream& os, const Lod_coef& l);

} // end of Vsp

#endif // LOD_COEF_H_INCLUDED

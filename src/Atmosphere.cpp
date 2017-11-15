/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Atmosphere.cpp                                                                                  */
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

#include <math.h>

#include "Atmosphere.h"


namespace Atmosphere {

// ISA functions
double temp(double alt)
{
    return isa_t_ground - (6.5 * (alt / 1000.0)); // 6.5 degree drop per 1000 m
}

double temp(double alt, double t_ground)
{
    return t_ground - (6.5 * (alt / 1000.0)); // 6.5 degree drop per 1000 m
}

double pres(double alt)
{
    return isa_p_ground * pow((1.0 - ((0.0065 * alt) / isa_t_ground)), 5.256);
}

double pres(double alt, double p_ground)
{
    return p_ground * pow((1.0 - ((0.0065 * alt) / isa_t_ground)), 5.256);
}

double dens(double alt)
{
    return   pres(alt) / ( spec_gas_const * temp(alt) );
}

double kin_visc(double alt)
{
    return ( 18.27 * pow( 10, -6.0 ) ) * ( ( 291.15 + 120.0 ) /
            ( temp(alt) + 120.0 ) ) *
            ( pow( ( temp(alt) / 291.15 ), 1.5 ) / dens(alt) );
}

double dyn_visc(double alt)
{
    return kin_visc(alt) * dens(alt);
}

double speed_of_sound(double alt)
{
    return sqrt( gamma * spec_gas_const * temp(alt) );
}

}

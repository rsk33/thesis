/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Atmosphere.h                                                                                    */
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

#ifndef ATMOSPHERE_H_INCLUDED
#define ATMOSPHERE_H_INCLUDED


// International Standard Atmosphere
namespace Atmosphere {

static constexpr double spec_gas_const = 287.058;   // specific gas constant [J/(kg*K)]
static constexpr double gamma = 1.4;                // heat capacity ratio [-]
static constexpr double isa_t_ground = 288.15;      // ISA temperature at sea level [K]
static constexpr double isa_p_ground = 101325;      // ISA pressure at sea level [Pa]


// ISA functions


// Temperature at given altitude [m] with standard ground temperature (288.15K) in [K]
double temp(double alt);

// Temperature at given altitude [m] in [K]
double temp(double alt, double t_ground);

// Static pressure at given altitude [m] with standard ground pressure (1013.25 hPa) in [Pa]
double pres(double alt);

// Static pressure at given altitude [m] in [Pa] : p_ground in [Pa]
double pres(double alt, double p_ground);

// Density in dependency of given pressure [Pa] and temperature [K] in [kg/m^3]
double dens(double alt);

// Kinematic Viscosity in dependency of Temperature [K] and density [kg/m^3] in [m^2/sec]
double kin_visc(double alt);


double dyn_visc(double alt);


double speed_of_sound(double alt);

};






#endif // ATMOSPHERE_H_INCLUDED

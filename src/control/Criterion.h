/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Criterion.h                                                                                     */
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

#ifndef CRITERION_H_INCLUDED
#define CRITERION_H_INCLUDED

#include <string>
#include <iostream>

namespace Control {

//===============================================================================================
//=== class Criterion ===//
// in-memory representation of criterion
class Criterion {
public:
    Criterion() {}
    Criterion(const std::string& parameter, const std::string& unit)
        :m_parameter{parameter}, m_unit{unit} {}

    std::string param_name() const { return m_parameter; }
    std::string unit() const { return m_unit; }

private:
    std::string m_parameter;
    std::string m_unit;
};

// operator overload to output criterion to console
std::ostream& operator<<(std::ostream& os, const Criterion& c);

}   // end of Control

#endif // CRITERION_H_INCLUDED

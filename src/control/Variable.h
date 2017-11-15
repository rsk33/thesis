/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Variable.h                                                                                      */
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

#ifndef VARIABLE_H_INCLUDED
#define VARIABLE_H_INCLUDED

#include <string>

namespace Control {

//===============================================================================================
//=== class Variable ===//
// in-memory representation of variable
class Variable {
public:
    Variable() {}
    Variable(const std::string& geom_name, const std::string& group_name,
             const std::string& param_name,
             double min_value, double max_value, double delta);

    const std::string& geom_name() const { return m_geom_name; }
    const std::string& group_name() const { return m_group_name; }
    const std::string& param_name() const { return m_param_name; }
    double min_value() const { return m_min_value; }
    double max_value() const { return m_max_value; }
    double delta() const { return m_delta; }
    std::string full_name() const;

private:
    std::string m_geom_name;
    std::string m_group_name;
    std::string m_param_name;
    double m_min_value;
    double m_max_value;
    double m_delta;
};

// operator overload to output variable to console
std::ostream& operator<<(std::ostream& os, const Variable& v);

}   // end of Control


#endif // VARIABLE_H_INCLUDED

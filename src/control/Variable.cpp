/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Variable.cpp                                                                                    */
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

#include <iostream>
#include <iomanip>
#include <string>

#include "Variable.h"

using namespace std;

namespace Control {

//===============================================================================================
//=== class Variable ===//


Variable::Variable(const string& geom_name, const string& group_name, const string& param_name,
                    double min_value, double max_value, double delta)
    :m_geom_name{geom_name},
    m_group_name{group_name},
    m_param_name{param_name},
    m_min_value{min_value},
    m_max_value{max_value},
    m_delta{delta}
{
}



string Variable::full_name() const
{
    return m_geom_name + '_' + m_group_name + '_' + m_param_name;
}

ostream& operator<<(ostream& os, const Variable& v)
{
    int l {30};   // left column
    os << "Variable\n"
        << setw(l) << left << "Geom_name:" << v.geom_name() << '\n'
        << setw(l) << left << "Group_name:" << v.group_name() << '\n'
        << setw(l) << left << "Param_name:" << v.param_name() << '\n'
        << setw(l) << left << "Min value:" << v.min_value() << '\n'
        << setw(l) << left << "Min value:" << v.max_value() << '\n'
        << setw(l) << left << "Delta:" << v.delta();
    return os;
}

}   // end of Control

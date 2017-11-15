/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Results.h                                                                                       */
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

#ifndef RESULTS_H_INCLUDED
#define RESULTS_H_INCLUDED

#include <vector>

#include "../control/Settings.h"
#include "../Initial_sizing.h"
#include "../Requirements.h"
#include "../vehicle/Aircraft.h"
#include "Var_polars.h"
#include "Horiz_stab_sizing.h"
#include "Range_des_report.h"

namespace Calculation {

// class used to store and manage results
class Results {
public:
    Results(const Control::Settings& settings, const Requirements& requirements,
            const Initial_sizing& initial_sizing)
        : m_settings{settings}, m_req{requirements}, m_init{initial_sizing} {}

    bool optimum(double& var, double& crit) const;
    bool outp_gaf(const Vehicle::Aircraft& aircraft) const;
    bool outp_des_study() const;
    void show_des_study() const;
    bool outp_polar() const;
    void add_polar(const Vehicle::Aircraft& aircraft, double var);
    void add_pair(double var, double val) { m_des_study.push_back(make_pair(val, var)); }
    void add_horiz_stab_sizing(Horiz_stab_sizing sizing) { m_horiz_stab_sizing.push_back(sizing); }
    void add_range_des_report(Range_des_report report) { m_range_des_reports.push_back(report); }
    bool outp_horiz_stab_sizing() const;

private:
    Control::Settings m_settings;
    Requirements m_req;
    Initial_sizing m_init;
    std::vector<std::pair<double,double>> m_des_study;
    std::vector<Var_polars> m_var_polars;
    std::vector<Horiz_stab_sizing> m_horiz_stab_sizing;
    std::vector<Range_des_report> m_range_des_reports;

};

}   // Calculation


#endif // RESULTS_H_INCLUDED

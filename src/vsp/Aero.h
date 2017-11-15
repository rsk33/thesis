/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Aero.h                                                                                          */
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

#ifndef AERO_H_INCLUDED
#define AERO_H_INCLUDED

namespace Vsp {

class Aero {
public:
    Aero(double ref_area, double ref_span, double ref_chord,
        const std::tuple<double,double,double>& cg,
        const std::vector<double>& mach, const std::vector<double>& aoa,
        const std::vector<double>& beta, int wakeiters, bool symm,
        int threads, bool stab, std::string file_rel_path);

    // non-modifying member functions
    std::string file_rel_path() const { return m_file_rel_path; }
    int threads() const { return m_threads; }
    bool stab() const { return m_stab; }
    std::string setup() const { return m_setup; }

private:
    std::string m_file_rel_path;    // VSPAero analysis model relative path
    int m_threads;                  // number of threads to be used in VSPAero analysis
    bool m_stab;                    // stability analysis, true - on, false - off
    std::string m_setup;            // string with vspaero setup (used in command line call)

};


} // end of Vsp

#endif // AERO_H_INCLUDED

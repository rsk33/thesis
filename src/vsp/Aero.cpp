/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Aero.cpp                                                                                        */
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

#include <string>
#include <vector>
#include <tuple>
#include "Aero.h"

#include <iostream>

using namespace std;

namespace Vsp {

// Aero constructor
Aero::Aero(double ref_area, double ref_span, double ref_chord,
            const tuple<double,double,double>& cg, const vector<double>& mach,
            const vector<double>& aoa, const vector<double>& beta, int wakeiters,
            bool symm, int threads, bool stab, string file_rel_path)
{
    string s_ref_area = " -sref " + to_string(ref_area) + ' ';

    string s_ref_span = " -bref " + to_string(ref_span) + ' ';

    string s_ref_chord = " -cref " + to_string(ref_chord) + ' ';

    string s_cg = " -cg " + to_string(get<0>(cg)) + ' '
                            + to_string(get<1>(cg)) + ' '
                            + to_string(get<2>(cg)) + ' ';

    string s_mach = " -mach ";
    for(auto x : mach)
        s_mach += to_string(x) + ' ';
    s_mach += "END ";

    string s_aoa = " -aoa ";
    for(auto x : aoa)
        s_aoa += to_string(x) + ' ';
    s_aoa += "END ";

    string s_beta = " -beta ";
    for(auto x : beta)
        s_beta += to_string(x) + ' ';
    s_beta += "END ";

    string s_wakeiters = " -wakeiters " + to_string(wakeiters) + ' ';

    string s_symm;
    if(symm) s_symm = " -symy ";

    string name = file_rel_path;
    name.erase(name.end()-4, name.end()); // remove extension .vsp3

    string setup = " -setup " + s_ref_area + s_ref_span + s_ref_chord +
                    s_cg + s_mach + s_aoa + s_beta + s_wakeiters + s_symm + name;

    m_file_rel_path = file_rel_path;
    m_threads = threads;
    m_stab = stab;
    m_setup = setup;
}


} // end of Vsp

/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Script.cpp                                                                                      */
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

#include <fstream>
#include <regex>

#include "Script.h"

using namespace std;

namespace Vsp {

// script constructor
Script::Script(Script_type script_type,
                const map<string,string>& key_value_set)
{
    string script_template_name = name(script_type);

    m_full_path = write(script_template_name, key_value_set);
}

// create a script out of the template
string Script::write(const string& script_template_name,
                     const map<string,string>& key_value_set) const
{
    string in_script_name = "scripts/" + script_template_name;
    string out_script_name = script_template_name;

    ifstream ifs {in_script_name};
    if(!ifs)
        throw runtime_error(in_script_name);

    ofstream ofs{out_script_name};
    if(!ofs)
        throw runtime_error(out_script_name);

    string readout;

    // replace keys by values
    while(getline(ifs,readout)){
        for(auto p : key_value_set)
            readout = regex_replace(readout, regex(p.first), p.second);
        ofs << readout << '\n';
    }
    return out_script_name;
}

// function returns a script name
string Script::name(Script_type& script_type) const
{
    switch (script_type) {
    case Script::compute_comp_geom:
        return "compute_comp_geom.vspscript";

    case Script::compute_degen_geom:
        return "compute_degen_geom.vspscript";

    case Script::modify_geom_param:
        return "modify_geom_param.vspscript";

    case Script::write_vspaero_model:
        return "write_vspaero_model.vspscript";

    case Script::export_tri_file:
        return "export_tri_file.vspscript";

    default:
        throw invalid_argument("script_type");
    }
}

} // end of Vsp

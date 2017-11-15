/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Script.h                                                                                        */
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

#ifndef SCRIPT_H_INCLUDED
#define SCRIPT_H_INCLUDED

#include <string>
#include <map>

namespace Vsp {

class Script {
public:
    // types of script templates
    enum Script_type {
        compute_comp_geom,
        compute_degen_geom,
        modify_geom_param,
        write_vspaero_model,
        export_tri_file,
    };

    // script constructor creates a script out of the template defined by the script type argument
    // by replacing all the keys in the template by the correspondent values form the key-value set
    Script(Script_type script_type,
           const std::map<std::string,std::string>& key_value_set);

    // function returns a script full path as a string
    std::string full_path() const { return m_full_path; }

private:
    std::string m_full_path;

    // function converts script type to string
    std::string name(Script_type& script_type) const;

    // function makes a script out of a template
    std::string write(const std::string& script_template_name,
                        const std::map<std::string,std::string>& key_value_set) const;
};


} // end of Vsp


#endif // SCRIPT_H_INCLUDED

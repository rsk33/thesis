/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Process.h                                                                                       */
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

#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

#include <string>
#include <vector>
#include <tuple>

#include "Script.h"
#include "Aero.h"
#include "Comp_geom.h"
#include "Polar.h"
#include "Lod.h"
#include "Stab.h"

namespace Vsp {

// process class represents vsp interface processes
class Process {
public:
    // process is constructed with a string of the vsp directory
    Process(const std::string& vsp_dir);

    // function executes a script
    bool execute(const Script& script) const;

    // function executes a vspaero analysis
    bool execute(const Aero& aero) const;

private:
    std::string m_vsp_dir;  // address of vsp directory
};

bool command_line(const std::string& call_argument);

// error() simply disguises throws:
inline void error(const std::string& s)
{
	throw std::runtime_error(s);
}

inline void error(const std::string& s, const std::string& s2)
{
	error(s + ' ' + s2);
}

} // end of Vsp


#endif // PROCESS_H_INCLUDED

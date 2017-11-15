/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Process.cpp                                                                                     */
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
#include <windows.h>

#include "Process.h"


using namespace std;

namespace Vsp {

// process constructor
Process::Process(const string& vsp_dir)
    : m_vsp_dir{vsp_dir}
{
    // check if vsp can be executed by with provided path
    if(!command_line(vsp_dir + "vspscript"))
        error("Error constructing Vsp::Process path", vsp_dir);
}

// function executes a script
bool Process::execute(const Script& script) const
{
    cout << "->VSP call\n";
    string command_line_arg = m_vsp_dir + "vspscript -script " + script.full_path();
    if(!command_line(command_line_arg)){
        error("Could not execute script",script.full_path());
        return false;
    }

    remove(script.full_path().c_str());
    return true;
}

// function executes a vspaero analysis
bool Process::execute(const Aero& a) const
{
    cout << "->VSPAero call - VSPAero setup creation\n";
    string command_line_arg = m_vsp_dir + "vspaero " + a.setup();
    if(!command_line(command_line_arg)){
        error("Could not execute ",a.setup());
        return false;
    }

    string s_threads = " -omp " + to_string(a.threads()) + ' ';
    string s_stab;
    if(a.stab()) s_stab = " -stab ";
    string name = a.file_rel_path();
    name.erase(name.end()-4, name.end()); // remove extension .vsp3
    string arg = s_threads + s_stab + name;

    cout << "->VSPAero call - analysis execution\n";
    command_line_arg = m_vsp_dir + "vspaero " + arg;
    if(!command_line(command_line_arg)){
        error("Could not execute ",arg);
        return false;
    }
    return true;
}

// function executes a process in a command line
bool command_line(const string& call_argument)
{
    LPSTR cmdArg = const_cast<char *>(call_argument.c_str());

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    // Start the child process.
    if(!CreateProcess(0, cmdArg, 0, FALSE, 0, 0, 0, 0, &si, &pi))
        return false;

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );

    // Close process and thread handles.
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );

    return true;
}

} // end of Vsp

/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Main.cpp                                                                                        */
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
#include <string>
#include <windows.h>

#include "src/Requirements.h"
#include "src/Initial_sizing.h"
#include "src/Design_input.h"
#include "src/std_lib_facilities.h"
#include "src/control/File_type.h"
#include "src/control/Settings.h"
#include "src/calculation/Analysis.h"


using namespace std;

int main()
try
{
    /// read settings
    Control::Settings settings{"general_settings_file.xml"};
    cout << settings << '\n';

    /// read requirements
    Requirements req{settings.file_name(Control::File_type::requirements)};
    cout << req << '\n';

    /// read initial sizing
    Initial_sizing init{settings.file_name(Control::File_type::initial_sizing)};
    cout << init << '\n';

    /// read design input
    Design_input des_inp{settings.file_name(Control::File_type::design_input)};
    cout << des_inp << '\n';

    // copy VSP model
    CopyFile(settings.file_name(Control::File_type::vsp).c_str(),
            settings.file_name(Control::File_type::vsp_new).c_str(),false);

    // make instance of analysis
    Calculation::Analysis analysis(settings, req, init);

    // make instance of aircraft
    Vehicle::Aircraft aircraft{req,init,des_inp};

    /// design study
    analysis.design_to_range(aircraft);

    /// horizontal stabilizer sizing
    analysis.horiz_stab_sizing(aircraft);

    // show aircraft to console
    cout << aircraft << '\n';

    /// general aircraft file output
    analysis.results().outp_gaf(aircraft);

    // delete temporary files
    settings.delete_temp_files();

    // wait till user reads results
    keep_window_open();

    return 0;
}
catch(exception& e){
    cerr << "error: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch(...){
    cerr << "unknown exception!\n";
    keep_window_open();
    return 2;
}

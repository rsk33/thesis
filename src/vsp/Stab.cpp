/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Stab.cpp                                                                                        */
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
#include <vector>

#include "Stab.h"

using namespace std;

namespace Vsp {

// operator overload to read an individual stability file entry
istream& operator>>(istream& ist, Stab& s)
{
    string line;
    double d;

    // skip lines
    for(int i{}; i<3; ++i){
        getline(ist,line);
    }
    // read parameter block
    ist >> s.param;

    // skip lines
    for(int i{}; i<5; ++i){
        getline(ist,line);
    }

    // read base coefficients
    ist >> line >> d >> line >> s.coef;

    // skip lines
    for(int i{}; i<15; ++i){
        getline(ist,line);
    }

    // read derivatives
    ist >> s.deriv;
    for(int i{}; i<4; ++i){
        getline(ist,line);
    }

    return ist;
}

// output operator overload
ostream& operator<<(ostream& os, const Stab& s)
{
    os << s.param   << "\n\n"
        << s.coef   << "\n\n"
        << s.deriv << '\n';
    return os;
}

// function reads vspaero stability output file into container of Stab data type
void fill_vector(istream& ist, vector<Stab>& s)
{
    // read all individual entries
    for(char ch; ist.get(ch) && ch == '*';)
    {
        Stab stab;
        ist >> stab;
        s.push_back(stab);
    }
}


} // end of Vsp

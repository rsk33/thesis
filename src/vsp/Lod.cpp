/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Lod.cpp                                                                                         */
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
#include <iomanip>

#include "Lod.h"

using namespace std;

namespace Vsp {

// operator overload to read-in a single loads file entry
istream& operator>>(istream& ist, Lod& l)
{
    string line;

    // skip lines
    for(int i{}; i<3; ++i){
        getline(ist,line);
    }

    // read a parameters block
    ist >> l.param;

    // skip lines till components block
    while(getline(ist,line)){
        if(line.compare(0,4,"Comp") == 0){
            break;
        }
    }

    // read in all components
    for(Comp comp; ist>>comp;){
        l.comps.push_back(comp);
    }

    // skip lines
    for(int i{}; i<3; ++i){
        getline(ist,line);
    }

    ist.clear();

    return ist;
}

// show vspaero loads file to console operator overload
ostream& operator<<(ostream& os, const Lod& l)
{
    os << l.param << "\n\n";

    for(auto x : l.comps){

        cout << x << '\n';
    }

    return os;
}

// function to read a vspaero loads file into container of load data structure
void fill_vector(istream& ist, vector<Lod>& l)
{
    string line;

    // read all the individual entries
    for(char ch; ist.get(ch) && ch == '*';)
    {
        Lod lod;
        ist >> lod;
        l.push_back(lod);
    }
}

} // end of Vsp

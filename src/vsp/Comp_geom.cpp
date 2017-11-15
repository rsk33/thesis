/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Comp_geom.cpp                                                                                   */
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

#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>

#include "Comp_geom.h"

using namespace std;

namespace Vsp {


// input operator overload. read string and create Comp_geom instance
istream& operator>>(istream& is, Comp_geom& c)
{
    is >> c.name >> c.theor_area >> c.wett_area >> c.theor_vol >> c.wett_vol;

    return is;
}

// output operator overload
ostream& operator<<(ostream& os, Comp_geom& c)
{
    int a{15};
    os << setw(a) << right << c.name
        << setw(a) << right << c.theor_area
        << setw(a) << right << c.wett_area
        << setw(a) << right << c.theor_vol
        << setw(a) << right << c.wett_vol;
    return os;
}

// function to read in vsp comp geom output file into container of Comp_geom data type
void fill_vector(istream& ist, vector<Comp_geom>& v)
{
    Comp_geom c;
    string line;

    getline(ist,line);             // skip a header line

    while(getline(ist,line))       // read all the lines and store records
    {
        if(line.empty()) break;
        replace(line.begin(),line.end(),',',' ');
        istringstream iss {line};
        iss >> c;           // read single component values
        v.push_back(c);
    }
}


} // end of Vsp

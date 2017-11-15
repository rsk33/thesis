/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           std_lib_facilities.h                                                                            */
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

#ifndef STD_LIB_FACILITIES_H_INCLUDED
#define STD_LIB_FACILITIES_H_INCLUDED

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>


using namespace std;


#define PI 3.14159265

namespace Constants {

const double gravity = 9.81;

}

// patch to convert data types to string
template<class T> string to_string(const T& t)
{
	ostringstream os;
	os << t;
	return os.str();
}

// error() simply disguises throws:
inline void error(const string& s)
{
	throw runtime_error(s);
}

// concatenate error strings
inline void error(const string& s, const string& s2)
{
	error(s + ' ' + s2);
}

// The call to keep_window_open() is needed on some Windows machines to prevent
// them from closing the window before you have a chance to read the output.
inline void keep_window_open()
{
    cin.get();
}


#endif // STD_LIB_FACILITIES_H_INCLUDED

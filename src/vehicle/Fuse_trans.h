/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Fuse_trans.h                                                                                    */
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

#ifndef FUSE_TRANS_H_INCLUDED
#define FUSE_TRANS_H_INCLUDED



#include <iostream>

#include "Component.h"
#include "Fuselage.h"

namespace Vehicle {

// class to represent transport fuselage - custom components of VSP
class Fuse_trans : public Fuselage {
public:
    Fuse_trans() {}
    Fuse_trans(const Fuselage& fuselage,
             double nose_length, double aft_length);

    double nose_length() const { return m_nose_length; }
    double aft_length() const { return m_aft_length; }

private:
    double m_nose_length{};
    double m_aft_length{};

};

std::ostream& operator<<(std::ostream& os, const Fuse_trans& f);


}



#endif // FUSE_TRANS_H_INCLUDED

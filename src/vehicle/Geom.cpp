/************************************************************************************************************************/
/* Project Name:        CAiDAS - Conceptual Aircraft Design Analysis and Optimization Software                          */
/* File Name:           Geom.cpp                                                                                        */
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

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include "Geom.h"
#include "../../TinyXML/tinyxml2.h"
#include "../vehicle/Aircraft.h"
#include "../vehicle/Fuse_trans.h"
#include "../std_lib_facilities.h"


using namespace std;

namespace Vehicle {

// read component parameters form vsp xml file
void read_geom(Vehicle::Component& component, tinyxml2::XMLElement* pParmContainer)
{
    using tinyxml2::XMLNode;
    using tinyxml2::XMLElement;

    XMLElement* pName = pParmContainer->FirstChildElement("Name");

    if(pName == NULL) error("Error: Could not access Name Element");

    string id = pName->GetText();

    XMLElement* pXform = pParmContainer->FirstChildElement("XForm");

    if(pXform == NULL) error("Error: Could not access XForm Element");

    XMLElement* pX_location = pXform->FirstChildElement("X_Location");

    double x_loc;

    pX_location->QueryDoubleAttribute("Value", &x_loc);

    if(pX_location == NULL) error("Error: Could not access X_Location Element");

    XMLElement* pY_location = pXform->FirstChildElement("Y_Location");

    double y_loc;

    pY_location->QueryDoubleAttribute("Value", &y_loc);

    if(pY_location == NULL) error("Error: Could not access Y_Location Element");

    XMLElement* pZ_location = pXform->FirstChildElement("Z_Location");

    double z_loc;

    pZ_location->QueryDoubleAttribute("Value", &z_loc);

    if(pZ_location == NULL) error("Error: Could not access Z_Location Element");

    Vehicle::Coord_sys loc = {x_loc, y_loc, z_loc};

    XMLElement* pX_rotation = pXform->FirstChildElement("X_Rotation");

    double x_rot;

    pX_rotation->QueryDoubleAttribute("Value", &x_rot);

    if(pX_rotation == NULL) error("Error: Could not access X_Rotation Element");

    XMLElement* pY_rotation = pXform->FirstChildElement("Y_Rotation");

    double y_rot;

    pY_rotation->QueryDoubleAttribute("Value", &y_rot);

    if(pY_rotation == NULL) error("Error: Could not access Y_Rotation Element");

    XMLElement* pZ_rotation = pXform->FirstChildElement("Z_Rotation");

    double z_rot;

    pZ_rotation->QueryDoubleAttribute("Value", &z_rot);

    if(pZ_rotation == NULL) error("Error: Could not access Z_Rotation Element");

    Vehicle::Coord_sys rot = {x_rot, y_rot, z_rot};

    XMLElement* pSym = pParmContainer->FirstChildElement("Sym");

    if(pSym == NULL) error("Error: Could not access Sym Element");

    XMLElement* pSym_Planar_Flag = pSym->FirstChildElement("Sym_Planar_Flag");

    int planar_sym {};

    pSym_Planar_Flag->QueryIntAttribute("Value", &planar_sym);

    bool symm_xz {};

    if(planar_sym == 2) // vsp internal flag for planar symmetry "2"
        symm_xz = true;

    component = Vehicle::Component{id, loc, rot, symm_xz};
}

// read fuselage parameters for vsp xml file
void read_geom(Vehicle::Fuselage& fuselage, tinyxml2::XMLElement* pParmContainer)
{
    using tinyxml2::XMLNode;
    using tinyxml2::XMLElement;

    Vehicle::Component comp;
    read_geom(comp, pParmContainer);


    XMLElement* pDesign = pParmContainer->FirstChildElement("Design");

    if(pDesign == NULL) error("Error: Could not access Design Element");

    XMLElement* pLength = pDesign->FirstChildElement("Length");

    if(pLength == NULL) error("Error: Could not access Length Element");

    double length{};

    pLength->QueryDoubleAttribute("Value", &length);

  //  XMLElement* pFuselageGeom = pGeom->FirstChildElement("FuselageGeom");
    XMLElement* pFuselageGeom = pParmContainer->NextSiblingElement("FuselageGeom");

    if(pFuselageGeom == NULL) error("Error: Could not access FuselageGeom Element");

    XMLElement* pXSecSurf = pFuselageGeom->FirstChildElement("XSecSurf");

    if(pXSecSurf == NULL) error("Error: Could not access XSecSurf Element");

    XMLElement* pXSec = pXSecSurf->FirstChildElement("XSec");

    if(pXSec == NULL) error("Error: Could not access XSec Element");

    // fuselage geometry is represented by number of sections
    vector<double> width_list;
    vector<double> height_list;

    //  read all sections height and width values
    while(true)
    {
        pXSec = pXSec->NextSiblingElement("XSec");

        if(pXSec == NULL) error("Error: Could not access XSec Element");

        XMLElement* pXSecL = pXSec->FirstChildElement("XSec");

        if(pXSecL == NULL) error("Error: Could not access XSec Element");

        XMLElement* pXSecCurve = pXSecL->FirstChildElement("XSecCurve");

        if(pXSecCurve == NULL) error("Error: Could not access XSecCurve Element");

        pParmContainer = pXSecCurve->FirstChildElement("ParmContainer");

        if(pParmContainer == NULL) error("Error: Could not access ParmContainer Element");

        pXSecCurve = pParmContainer->FirstChildElement("XSecCurve");

        if(pXSecCurve == NULL) error("Error: Could not access XSecCurve Element");

        XMLElement* pEllipse_Height = pXSecCurve->FirstChildElement("Ellipse_Height");

        if(pEllipse_Height == NULL) break;

        double height {};

        pEllipse_Height->QueryDoubleAttribute("Value", &height);

        height_list.push_back(height);

        XMLElement* pEllipse_Width = pXSecCurve->FirstChildElement("Ellipse_Width");

        double width {};

        pEllipse_Width->QueryDoubleAttribute("Value", &width);

        if(pEllipse_Width == NULL) error("Error: Could not access Ellipse_Width Element");

        width_list.push_back(width);
    }

    // sort values
    sort(width_list.begin(), width_list.end());
    sort(height_list.begin(), height_list.end());

    // max value is last element
    double width = width_list[width_list.size() - 1];
    double height = height_list[height_list.size() - 1];

    // find equivalent diam
    double diam = sqrt( width * height );

    fuselage = Vehicle::Fuselage{comp, length, diam};

}


void read_geom(Vehicle::Fuse_trans& fuse_trans, tinyxml2::XMLElement* pParmContainer)
{
    using tinyxml2::XMLNode;
    using tinyxml2::XMLElement;

    Vehicle::Component comp;
    read_geom(comp, pParmContainer);

    XMLElement* pDesign = pParmContainer->FirstChildElement("Design");

    if(pDesign == NULL) error("Error: Could not access Design Element");

    XMLElement* pLength = pDesign->FirstChildElement("Length");

    if(pLength == NULL) error("Error: Could not access Length Element");

    double length;

    pLength->QueryDoubleAttribute("Value", &length);

    XMLElement* pNoseMult = pDesign->FirstChildElement("NoseMult");

    if(pNoseMult == NULL) error("Error: Could not access NoseMult Element");

    double nose_mult;

    pNoseMult->QueryDoubleAttribute("Value", &nose_mult);

    XMLElement* pAftMult = pDesign->FirstChildElement("AftMult");

    if(pAftMult == NULL) error("Error: Could not access AftMult Element");

    double aft_mult;

    pAftMult->QueryDoubleAttribute("Value", &aft_mult);

    XMLElement* pDiameter = pDesign->FirstChildElement("Diameter");

    if(pDiameter == NULL) error("Error: Could not access Diameter Element");

    double diameter;

    pDiameter->QueryDoubleAttribute("Value", &diameter);

    fuse_trans = Vehicle::Fuse_trans{Vehicle::Fuselage{comp, length, diameter},(nose_mult * diameter),
                                    (aft_mult * diameter)};

}

// read wing parameters from vsp xml file
void read_geom(Vehicle::Wing& wing, tinyxml2::XMLElement* pParmContainer)
{
    using tinyxml2::XMLNode;
    using tinyxml2::XMLElement;

    Vehicle::Component comp;

    read_geom(comp, pParmContainer);

    XMLElement* pWingGeom = pParmContainer->NextSiblingElement("WingGeom");

    if(pWingGeom == NULL) error("Error: Could not access WingGeom Element");

    XMLElement* pXsecSurf = pWingGeom->FirstChildElement("XSecSurf");

    if(pXsecSurf == NULL) error("Error: Could not access XSecSurf Element");

    XMLElement* pXsec = pXsecSurf->FirstChildElement("XSec");

    if(pXsec == NULL) error("Error: Could not access Xsec Element");

    // read root section

    pXsec = pXsec->FirstChildElement("XSec");

    if(pXsec == NULL) error("Error: Could not access XSec Element");

    XMLElement* pXSecCurve = pXsec->FirstChildElement("XSecCurve");

    if(pXSecCurve == NULL) error("Error: Could not access XSecCurve Element");

    pParmContainer = pXSecCurve->FirstChildElement("ParmContainer");

    if(pParmContainer == NULL) error("Error: Could not access ParmContainer Element");

    pXSecCurve = pParmContainer->FirstChildElement("XSecCurve");

    if(pXSecCurve == NULL) error("Error: Could not access XSecCurve Element");

    XMLElement* pThickChord = pXSecCurve->FirstChildElement("ThickChord");

    if(pThickChord == NULL) error("Error: Could not access ThickChord Element");

    double root_thick;

    pThickChord->QueryDoubleAttribute("Value", &root_thick);


    // read wing section and tip section
    pXsec = pXsecSurf->FirstChildElement("XSec");

    pXsec = pXsec->NextSiblingElement("XSec");

    if(pXsec == NULL) error("Error: Could not access XSec Element");

    pParmContainer = pXsec->FirstChildElement("ParmContainer");

    if(pParmContainer == NULL) error("Error: Could not access ParmContainer Element");

    pXsec = pParmContainer->FirstChildElement("XSec");

    if(pXsec == NULL) error("Error: Could not access XSec Element");

    XMLElement* pArea = pXsec->FirstChildElement("Area");

    if(pArea == NULL) error("Error: Could not access Area Element");

    double area;

    pArea->QueryDoubleAttribute("Value", &area);

    XMLElement* pAspect = pXsec->FirstChildElement("Aspect");

    if(pAspect == NULL) error("Error: Could not access Aspect Element");

    double aspect;

    pAspect->QueryDoubleAttribute("Value", &aspect);

    XMLElement* pDihedral = pXsec->FirstChildElement("Dihedral");

    if(pDihedral == NULL) error("Error: Could not access Dihedral Element");

    double dihedral;

    pDihedral->QueryDoubleAttribute("Value", &dihedral);

    XMLElement* pRoot_Chord = pXsec->FirstChildElement("Root_Chord");

    if(pRoot_Chord == NULL) error("Error: Could not access Root_Chord Element");

    double root_chord;

    pRoot_Chord->QueryDoubleAttribute("Value", &root_chord);

    XMLElement* pSpan = pXsec->FirstChildElement("Span");

    if(pSpan == NULL) error("Error: Could not access Span Element");

    double span;

    pSpan->QueryDoubleAttribute("Value", &span);

    XMLElement* pSweep = pXsec->FirstChildElement("Sweep");

    if(pSweep == NULL) error("Error: Could not access Sweep Element");

    double sweep;

    pSweep->QueryDoubleAttribute("Value", &sweep);

    XMLElement* pSweep_Location = pXsec->FirstChildElement("Sweep_Location");

    if(pSweep_Location == NULL) error("Error: Could not access Sweep_Location Element");

    double sweep_loc;

    pSweep_Location->QueryDoubleAttribute("Value", &sweep_loc);

    XMLElement* pTaper = pXsec->FirstChildElement("Taper");

    if(pTaper == NULL) error("Error: Could not access Taper Element");

    double taper;

    pTaper->QueryDoubleAttribute("Value", &taper);

    XMLElement* pTip_Chord = pXsec->FirstChildElement("Tip_Chord");

    if(pTip_Chord == NULL) error("Error: Could not access Tip_Chord Element");

    double tip_chord;

    pTip_Chord->QueryDoubleAttribute("Value", &tip_chord);

    XMLElement* pTwist = pXsec->FirstChildElement("Twist");

    if(pTwist == NULL) error("Error: Could not access Tip_Chord Element");

    double twist;

    pTwist->QueryDoubleAttribute("Value", &twist);

    XMLElement* pTwist_Location = pXsec->FirstChildElement("Twist_Location");

    if(pTwist_Location == NULL) error("Error: Could not access Tip_Chord Element");

    double twist_loc;

    pTwist_Location->QueryDoubleAttribute("Value", &twist_loc);

    pXsec = pXsecSurf->FirstChildElement("XSec");

    if(pXsec == NULL) error("Error: Could not access XSec Element");

    pXsec = pXsec->NextSiblingElement("XSec");

    if(pXsec == NULL) error("Error: Could not access XSec Element");

    pXsec = pXsec->FirstChildElement("XSec");

    if(pXsec == NULL) error("Error: Could not access XSec Element");

    pXSecCurve = pXsec->FirstChildElement("XSecCurve");

    if(pXSecCurve == NULL) error("Error: Could not access XSecCurve Element");

    pParmContainer = pXSecCurve->FirstChildElement("ParmContainer");

    if(pParmContainer == NULL) error("Error: Could not access ParmContainer Element");

    pXSecCurve = pParmContainer->FirstChildElement("XSecCurve");

    if(pXSecCurve == NULL) error("Error: Could not access XSecCurve Element");

    pThickChord = pXSecCurve->FirstChildElement("ThickChord");

    if(pThickChord == NULL) error("Error: Could not access ThickChord Element");

    double tip_thick;

    pThickChord->QueryDoubleAttribute("Value", &tip_thick);



    wing = Vehicle::Wing{comp, area, span, aspect,
                            taper, tip_chord, tip_thick, root_chord, root_thick,
                            sweep, sweep_loc, twist, twist_loc, dihedral};
}

// read aircraft from vsp xml file
void read_geom(Vehicle::Aircraft& aircraft, const string& file_name)
{
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLNode;
    using tinyxml2::XMLElement;

    XMLDocument doc;

    doc.LoadFile(file_name.c_str());

    if(doc.Error()) error("Could not open XML-File");

    XMLNode* pVsp_Geometry = doc.FirstChildElement();

    if(pVsp_Geometry == NULL) error("Error: Could not access Vsp_Geometry Node");

    XMLElement* pVehicle = pVsp_Geometry->FirstChildElement("Vehicle");

    if(pVehicle == NULL) error("Error: Could not access Vehicle Element");

    int geom_node {};       // variable used to count geom node of vsp3 file

    Vehicle::Fuselage fuselage;
    vector<Vehicle::Wing> wings;

    // Loop through geometry nodes and add them to the aircraft
    while(true)
    {
        XMLElement* pGeom = pVehicle->FirstChildElement("Geom");

        // loop is implemented to iterate through geometries in the vsp3 file
        for(int i {}; i < geom_node ; ++i)
        {
            pGeom = pGeom->NextSiblingElement("Geom");
        }

        if(pGeom == NULL)
        {

            break;    // all geometries read, leaving the loop and function
        }

        // check wing or fuselage
        XMLElement* pWingGeom = pGeom->FirstChildElement("WingGeom");

        XMLElement* pFuselageGeom = pGeom->FirstChildElement("FuselageGeom");

        XMLElement* pParmContainer = pGeom->FirstChildElement("ParmContainer");

        if(pParmContainer == NULL) error("Error: Could not access ParmContainer Element");

        // read Fuselage
        if(pFuselageGeom != nullptr)
        {

            read_geom(fuselage, pParmContainer);

            ++geom_node;
        }

        // read Lifting Surface
        else if(pWingGeom != nullptr)
        {
            Vehicle::Wing wing;
            read_geom(wing, pParmContainer);
            wings.push_back(wing);

            ++geom_node;
        }
        else
        {
            cout << "NOTE: Currently ONLY Fuselage and Wing VSP Geometry Types can be "
                << "recognized.\nFile contains unknown components.\n\n";

           ++geom_node; // skip unrecognized geometry
        }
    }

    // identify main wing horizontal stab and vertical tail out of vector with wings

    // determine main wing which is assumed to have biggest area
    auto p_main_wing = max_element(wings.begin(), wings.end(), Vehicle::compare_area);

    if(p_main_wing == wings.end()){
        error("Main wing was not found");
    }

    int it_main_wing = distance(wings.begin(), p_main_wing);

    // determine vertical tail which is 90 DEG rotated with respect to X-axis
    auto p_vert_stab = find_if(wings.begin(), wings.end(), Vehicle::vertical);

    if(p_vert_stab == wings.end()){
        error("Vertical Stabilizer was not found");
    }

    int it_vert_stab = distance(wings.begin(), p_vert_stab);

    int it_horiz_stab{};

    // remaining wing must be horizontal stab
    for(int i{}; i<int(wings.size()); ++i)
        {
            if(i != it_main_wing && i != it_vert_stab)
                it_horiz_stab = i;
        }


    aircraft.fuselage() = fuselage;
    aircraft.main_wing() = wings[it_main_wing];
    aircraft.horiz_tail() = Vehicle::Horizontal_tail {wings[it_horiz_stab]};
    aircraft.vert_tail() = Vehicle::Vertical_tail {wings[it_vert_stab]};

}

}

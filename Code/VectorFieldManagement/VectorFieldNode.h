//
//  VectorFieldNode.h
//  Vector Field Visualizer
//
//  Created by Aaron Blasdel on 12/13/11.
//  Copyright (c) 2011 Aaron Blasdel. All rights reserved.
//
//  VectorFieldNode stores the location and direction data of a VectorField position 
//  in addition it stores all information needed to draw the Node
//

#ifndef Vector_Field_Visualizer_VectorFieldNode_h
#define Vector_Field_Visualizer_VectorFieldNode_h
#include "Point.h"

class VectorFieldNode{
    Point _position;        //Position in the Cube
    aVector _direction;     //Strength and direction of node force
    aMaterial _material;    //Color information
    float _thickness;       //Draw thickness of a vector 
public:
    // Constructors, Destructor and other bookkeeping functions
    VectorFieldNode () ;
//:BUG:  VectorFieldNodes.draw() is not coloring properly. tracked it here. The material being passed does not properly retain values.
    VectorFieldNode ( const Point, const aVector,const float newThickness=.005, const aMaterial = WhiteMaterial) ;
    VectorFieldNode ( const VectorFieldNode& ) ;
    virtual ~VectorFieldNode () ;
    VectorFieldNode& operator= ( const VectorFieldNode& ) ;

    // Member Access Functions
    Point     location () const { return _position ; } 
    aVector   direction() const { return _direction; } 
    aMaterial material () const { return _material ; } 
    float     thickness() const { return _thickness; }
    void setPosition (Point newlocationation)    { _position = newlocationation; } 
    void setDirection(aVector newdirection) { _direction= newdirection;} 
    void setMaterial (aMaterial newMaterial){ _material = newMaterial; } 
    void setThickness(float newThickness)   { _thickness= newThickness;}

    // Draw
    void draw();
};

#endif

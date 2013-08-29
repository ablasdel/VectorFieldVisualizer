//
//  VectorFieldNode.cpp
//  Vector Field Visualizer
//
//  Created by Aaron Blasdel on 12/13/11.
//  Copyright (c) 2011 Aaron Blasdel. All rights reserved.
//

#include <iostream>
#include "Material.h"
#include "VectorFieldNode.h"

VectorFieldNode::VectorFieldNode () 
{
    _thickness=.005;
}

VectorFieldNode::VectorFieldNode ( const Point newlocation, const aVector newdirection,const float newThickness, const aMaterial newMaterial) 
{
    _position=newlocation;
    _direction=newdirection;
    _thickness=newThickness;
    _material=newMaterial;
}

VectorFieldNode::VectorFieldNode ( const VectorFieldNode& newVFN) 
{
    _position=newVFN.location();
    _direction=newVFN.direction();
    _material=newVFN.material();
    _thickness=newVFN.thickness();
}

VectorFieldNode::~VectorFieldNode () 
{
    
}

VectorFieldNode& VectorFieldNode::operator= ( const VectorFieldNode& VFN ) 
{    
    if ( this == &VFN ) return ( *this ) ;
    _position = VFN.location();
    _direction = VFN.direction();
    return ( *this ) ;
}


// Draw
void VectorFieldNode::draw()
{
    aVector temp= _direction/_direction.length();
    temp.DrawFromPoint ( _material, _position, _thickness); 
}
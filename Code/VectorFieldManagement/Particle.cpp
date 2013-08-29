//
//  Particle.cpp
//  Vector Field Visualizer
//
//  Created by Aaron Blasdel on 12/13/11.
//  Copyright (c) 2011 Aaron Blasdel. All rights reserved.
//

#include <iostream>
#include "Particle.h"


Particle::Particle () 
{
} 

Particle::Particle ( const Point pos, const double weight, const aMaterial mat, const int life) 
{
    _position=pos;
    _weight=weight;
    _material=mat;
    _life=life;
}

Particle::Particle ( const Particle& newPart) 
{
    _position = newPart.position();
    _material = newPart.material();
    _weight = newPart.weight();
    _life = newPart.Life();
}

Particle::~Particle () 
{
}

Particle& Particle :: operator= ( const Particle& p ) 
{
    if ( this == &p ) return ( *this ) ;
    _position.xyz(p.position().x(),p.position().y(),p.position().z()) ;
    return ( *this ) ;
}

Particle operator+ ( const Particle& p1, const aVector& p2 ) 
{
    Point pp (p1.position().x() + p2.x(),
              p1.position().y() + p2.y(),
              p1.position().z() + p2.z()) ;    
    return ( Particle(pp,p1.weight(),p1.material(),p1.Life())) ;
}

Particle operator+ ( const aVector& p2, const Particle& p1 ) 
{
    Point pp (p1.position().x() + p2.x(),
              p1.position().y() + p2.y(),
              p1.position().z() + p2.z()) ;
    return ( Particle(pp,p1.weight(),p1.material(),p1.Life())) ;
}

Particle operator- ( const Particle& p1, const aVector& p2 ) 
{
    Point pp (p1.position().x() - p2.x(),
              p1.position().y() - p2.y(),
              p1.position().z() - p2.z()) ;    
    return ( Particle(pp,p1.weight(),p1.material(),p1.Life())) ;
}

Particle& Particle :: operator+= ( const aVector& v )
{
    _position.xyz(_position.x()+v.x(),_position.y()+v.y(),_position.z()+v.z());    
    return ( *this ) ;
}

Particle& Particle :: operator-= ( const aVector& v )
{
    _position.xyz(_position.x()-v.x(),_position.y()-v.y(),_position.z()-v.z());
    return ( *this ) ;
}

void Particle::draw()
{    
    _position.Draw(_material,_weight,50); //draw the sphere in 50 segments
}
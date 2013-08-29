//
//  Particle.h
//  Vector Field Visualizer
//
//  Created by Aaron Blasdel on 12/13/11.
//  Copyright (c) 2011 Aaron Blasdel. All rights reserved.
//
//  Stores all data to describe and draw a particle
//

#ifndef Vector_Field_Visualizer_Particle_h
#define Vector_Field_Visualizer_Particle_h
#include "GL3.h"
#include "Point.h"

class Particle{
    Point _position;        //Position in the cube
    double _weight;         //Size of Particle
    int _life;              //Time before death
    aMaterial _material;    //Color information
public:    
    // Constructors, Destructor and other bookkeeping functions
    Particle () ;
    Particle (const Point pos, 
              const double weight = 0.1, 
              const aMaterial mat = aMaterial(Color(0,1,0)), 
              const int life = 500) ;
    Particle ( const Particle& ) ;
    virtual ~Particle () ;
    Particle& operator= ( const Particle& ) ;
    friend Particle operator+ ( const Particle&, const aVector& ) ;
    friend Particle operator+ ( const aVector&, const Particle& ) ;
    friend Particle operator- ( const Particle&, const aVector& ) ;
    Particle& operator+= ( const aVector& ) ;
    Particle& operator-= ( const aVector& ) ;

    // Member Access Functions
    Point       position() const { return _position ; } 
    aMaterial   material() const { return _material ; } 
    double      weight  () const { return _weight ; } 
    int         Life    () const { return _life ; } 
    void setPosition(Point newPosition)     { _position = newPosition; } 
    void setMaterial(aMaterial newMaterial) { _material = newMaterial; } 
    void setWeight  (double newWeight)      { _weight   = newWeight ; } 
    void setLife    (double newLife)        { _life     = newLife ; } 
    void decLife()                          { _life--; } 

    // Draw
    void draw();
};

#endif

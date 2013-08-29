//
//  VectorField.h
//  Vector Field Visualizer
//
//  Created by Aaron Blasdel on 12/13/11.
//  Copyright (c) 2011 Aaron Blasdel. All rights reserved.
//
// VectorField primarily creates and manages a 3 dimensional space of vectors(math definition) which are anchored 
// in an evenly spaced manner throughout a cube. Secondarily it manages a set of Particles that exist somewhere inside
// the space and, with the use of the "moveParticles" function, moves them around the space according to their position
// relative to the nearest neighboring vectors.
// For ease of access vector field files are provided and are stored in the _files array.

#ifndef Vector_Field_Visualizer_VectorField_h
#define Vector_Field_Visualizer_VectorField_h
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <vector>
#include "VectorFieldNode.h"
#include "Particle.h"

using namespace std;

//returns a random float between min and max
class RandNum{
    static bool _randomized;
public:
    float frand(float min = 0.0,float max=1.0) 
    {
        if(!_randomized) 
        {   //if it isn't randomized yet randomize it
            srand ( (unsigned int) time(NULL) );
            _randomized=true;
        }
        return (max-min)*(float)rand()/(float)RAND_MAX + min;   
    }
};

class VectorField{
    vector<vector<vector<VectorFieldNode> > > _Field;
    vector<Particle> _particles;
    float _segmentSize;         //The uniform amount of space between two vector anchors
    float _minBound;            //Start of the cube
    float _maxBound;            //End of the cube
    vector<string> _files;      //Available files 
    long _fileIndex;            //Index (into _files) of the currently loaded file
    bool _particleOnlyMode;     //Draw only the particles if this is true
    float _particleSpeed;       //modifies the particle speed
public:
    // Constructor, Destructor and other bookkeeping functions
    VectorField ();
    virtual ~VectorField () ;
    VectorFieldNode& operator= ( const VectorFieldNode& ) ;

    // Particle management Functions
    void addParticle(Particle); //Adds a specific particle you construct
    void addParticle();         //Adds a particle at a random point within the cube
    void popParticle();         //Removes the last particle from _particles
    void moveParticles();       //Animates the particles based on vectorfield properties

    // File managment 
    void readFile();            //Loads _files[_filesindex] into _Field
    void nextFile();            //_fileIndex++ (list is considered circular)
    void prevFile();            //_fileIndex-- (list is considered circular)
    
    // Toggle Particle only mode
    void toggleDrawMode() {_particleOnlyMode=!_particleOnlyMode;}
    
    // Manipulate Overall Particle speed
    void incParticleSpeed() {_particleSpeed+=.1;}
    void decParticleSpeed() {_particleSpeed-=.1;}
    
    // Draw the vector field and particles
    void draw();


};

#endif

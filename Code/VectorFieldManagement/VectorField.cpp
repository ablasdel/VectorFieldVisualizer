//
//  VectorField.cpp
//  Vector Field Visualizer
//
//  Created by Aaron Blasdel on 12/13/11.
//  Copyright (c) 2011 Aaron Blasdel. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "VectorField.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

//initilize static random number generator
static RandNum frand; //call as so frand.frand();
bool RandNum::_randomized=false;

VectorField::VectorField ()
{
    //Set up cube bounds
    _minBound=-2.25;
    _maxBound=2.25;
    _particleSpeed=1.0;
    
    //Initially draw everything
    _particleOnlyMode=true;

    //Start the field out with 100 particles
    for(int i=0;i<100;i++) addParticle();   

    //Set up the list of files
    _fileIndex=0;
    _files.push_back("./Code/FieldFiles/center2.field");
    _files.push_back("./Code/FieldFiles/saddle.field");
    _files.push_back("./Code/FieldFiles/attractingnode.field");
    _files.push_back("./Code/FieldFiles/repellingfocus.field");
    _files.push_back("./Code/FieldFiles/nonconst.field");
//    _files.push_back("./Code/FieldFiles/const.field");
//    _files.push_back("./Code/FieldFiles/center.field");
//    _files.push_back("./Code/FieldFiles/unsteadyhelices.field");
    readFile();
}

VectorField::~VectorField () 
{
    _Field.clear();
    _particles.clear();
}

void VectorField::addParticle(Particle newParticle)
{
    _particles.push_back(newParticle);
}


void VectorField::addParticle()
{
    //Add a particle to the list at a random point in the cube
    //The Weight is randomly chosen (frand.frand(.02,.06))
    addParticle(Particle(Point(frand.frand(_minBound,_minBound),frand.frand(_minBound,_minBound),frand.frand(_minBound,_minBound)),frand.frand(.02,.06)));      
}

void VectorField::popParticle()
{
    if (_particles.size()>0) _particles.erase(_particles.end());
}

void VectorField::moveParticles()
{
    //Vector influence on a Particle is determined through a process of successive linear interpolations.
    //Particle movement could be smoothed with the use of quadratic interpolation but would require 
    //padding the data with an extra unused segment 
    int xIndex,yIndex,zIndex;
    
    aVector zMidVector[4],yMidVector[2],moveVector;
    Point zMidPoint[4],yMidPoint[2];
    for (unsigned int Part=0; Part<_particles.size(); Part++) 
    {
        //store the current position for later use
        Point curPos=_particles[Part].position();
        
        //map the current particle position into _field indices
        xIndex=(curPos.x()-_minBound)/_segmentSize;
        yIndex=(curPos.y()-_minBound)/_segmentSize;
        zIndex=(curPos.z()-_minBound)/_segmentSize;

        //linearly interpolate Index pairs of vectors on the z axis and keep track of the midpoint location for subiquent interpolation.
        //Code spacing optimized to minimize one off interpolation errors
        zMidVector[0]=
                (-_Field[xIndex  ][yIndex  ][zIndex  ].location().z()+curPos.z())
                 *_Field[xIndex  ][yIndex  ][zIndex  ].direction()+
                ( _Field[xIndex  ][yIndex  ][zIndex+1].location().z()-curPos.z())
                 *_Field[xIndex  ][yIndex  ][zIndex+1].direction();
        zMidPoint[0] = midpoint(
                  _Field[xIndex  ][yIndex  ][zIndex  ].location(),
                  _Field[xIndex  ][yIndex  ][zIndex+1].location());

        zMidVector[1]=
                (-_Field[xIndex  ][yIndex+1][zIndex  ].location().z()+curPos.z())
                 *_Field[xIndex  ][yIndex+1][zIndex  ].direction()
               +( _Field[xIndex  ][yIndex+1][zIndex+1].location().z()-curPos.z())
                 *_Field[xIndex  ][yIndex+1][zIndex+1].direction();
        zMidPoint[1] = midpoint(
                  _Field[xIndex  ][yIndex+1][zIndex  ].location(),     
                  _Field[xIndex  ][yIndex+1][zIndex+1].location());
        
        zMidVector[2]=
                (-_Field[xIndex+1][yIndex  ][zIndex  ].location().z()+curPos.z())
                 *_Field[xIndex+1][yIndex  ][zIndex  ].direction()
               +( _Field[xIndex+1][yIndex  ][zIndex+1].location().z()-curPos.z())
                 *_Field[xIndex+1][yIndex  ][zIndex+1].direction();
        zMidPoint[2] = midpoint(
                  _Field[xIndex+1][yIndex  ][zIndex  ].location(),     
                  _Field[xIndex+1][yIndex  ][zIndex+1].location());

        zMidVector[3]=
                (-_Field[xIndex+1][yIndex+1][zIndex  ].location().z()+curPos.z())
                 *_Field[xIndex+1][yIndex+1][zIndex  ].direction()
               +( _Field[xIndex+1][yIndex+1][zIndex+1].location().z()-curPos.z())
                 *_Field[xIndex+1][yIndex+1][zIndex+1].direction();
        zMidPoint[3] = midpoint(
                  _Field[xIndex+1][yIndex+1][zIndex  ].location(),    
                  _Field[xIndex+1][yIndex+1][zIndex+1].location());

        //linearly interpolate between pairs of vectors on the y axis and keep track of the midpoint location for subiquent interpolation.
        yMidVector[0]
                =(-zMidPoint[0].y()+curPos.y())*zMidVector[0]
                +( zMidPoint[1].y()-curPos.y())*zMidVector[1];
        yMidPoint[0]= midpoint(zMidPoint[0],zMidPoint[1]);
        
        yMidVector[1]
                =(-zMidPoint[2].y()+curPos.y())*zMidVector[2]
                +( zMidPoint[3].y()-curPos.y())*zMidVector[3];
        yMidPoint[1]= midpoint(zMidPoint[2],zMidPoint[3]);
        
        //finally linearly interpolate between pairs of vectors on the x axis and move the stored particle by the resulting vector
        //reduce the movement speed based on the weight of the particle
        curPos+=(_particleSpeed/10)*
                (1-(10*_particles[Part].weight()))*
                ((-yMidPoint[0].x()+curPos.x())*yMidVector[0]
               +(  yMidPoint[1].x()-curPos.x())*yMidVector[1]);
        
        //test if the moved particle is still in the field
        //if is still in the field set the position 
        //else randomly generate a new position for it inside the field
        if (max(max(curPos.x(),curPos.y()),curPos.z())>_maxBound||min(min(curPos.x(),curPos.y()),curPos.z())<_minBound)
            _particles[Part].setPosition(Point(frand.frand(_minBound,_maxBound),frand.frand(_minBound,_maxBound),frand.frand(_minBound,_maxBound)));
        else
            _particles[Part].setPosition(curPos);            
    }
}

void VectorField::draw()
{
    //Draw each Particle in _particles ...
    for(std::vector<Particle>::iterator it = _particles.begin(); it != _particles.end(); ++it)
        it->draw();    
    //...and each VectorFieldNode in the _Field
    if (!_particleOnlyMode)
        for (unsigned int i=0; i<_Field.size(); i++) 
            for (unsigned int j=0; j<_Field[i].size(); j++) 
                for (unsigned int k=0; k<_Field[i][j].size(); k++) 
                    _Field[i][j][k].draw();
}

void VectorField::readFile()
{
    //File Format:
    //The first line is a single int denoting the size of the cube
    //(size^3)*3 lines of floats each 3 line group denotes a Vector as so Vector(line1,line2,line3)
    
    unsigned int dataSize = 0;                  //number of rows,cols and planes in the data cube
    double data[3];                             //scratch pad for reading from file
    ifstream fd(_files[_fileIndex].c_str());    //Opens the current index into _files
    if(!fd.is_open())
    {
        _files[_fileIndex].replace(1,5,"");     //removes the "/Code/ directory from the string
        fd.open(_files[_fileIndex].c_str());    //try to open again
        if(!fd.is_open())
        {
            cout<<"Failed to find vector field files. This program must be launched from the command line."<<endl;
            exit(1);
        }
    }
    fd>>dataSize;                               //Reads the dataSize from file

    //if the _Field needs to be resized do so
    if (_Field.size()!=dataSize )
    {
        _Field.resize(dataSize);
        for (unsigned int i=0; i<dataSize; i++) 
        {
            _Field[i].resize(dataSize);
            for (unsigned int j=0; j<dataSize; j++)
                _Field[i][j].resize(dataSize);
        }
    }
    
    //set the size of a segment based on the number of points in the datachunk
    _segmentSize=(_maxBound-_minBound)/(dataSize-1);
    
    for(unsigned int k = 0; k < dataSize; k++)
        for(unsigned int i = 0; i < dataSize; i++)
           for(unsigned int j = 0; j < dataSize; j++)
           {
               //read data
               fd>>data[0]; fd>>data[1]; fd>>data[2];
               //map the vectors to be equally spaced between _minBound and _maxBound
               //Data is scaled down by 128 to be more easily viewable in "cubespace"
               _Field[i][j][k]=VectorFieldNode(Point(i*_segmentSize+_minBound,j*_segmentSize+_minBound,k*_segmentSize+_minBound),
                                               aVector(data[0],data[1],data[2]));
           }
}

void VectorField::nextFile() 
{   
    if (++_fileIndex > (long)_files.size()-1) _fileIndex=0;
    readFile();
}

void VectorField::prevFile()
{
    if (--_fileIndex < 0) _fileIndex = _files.size()-1;
    readFile();
}

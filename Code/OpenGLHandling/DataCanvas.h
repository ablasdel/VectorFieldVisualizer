//
//  DataCanvas.h
//  Vector Field Visualizer
//
//  Created by Aaron Blasdel on 12/16/11.
//  Copyright (c) 2011 Aaron Blasdel. All rights reserved.
//

#ifndef Vector_Field_Visualizer_DataCanvas_h
#define Vector_Field_Visualizer_DataCanvas_h
#include "VectorField.h"
#include "GLCanvas.h"

class DataCanvas: public GLCanvas{
private:
    //_theField must be static to be accessed in GLUT Callback functions
    static VectorField _theField;//Field data 
public:
    static void DrawCallback(); //Override callback to draw _theField
    static void IdleCallback(); //Override callback to animate _theField
    static void KeyboardCallback(unsigned char key, int x, int y); //Override callback to manipulate _theField
    void initilize(int argc, char ** argv,string = "Default GLCanvas Window"); //Override initialize to set new callbacks
};

#endif

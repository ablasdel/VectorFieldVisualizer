//
//  GLCanvas.h
//  Vector Field Visualizer
//
//  Created by Aaron Blasdel on 12/13/11.
//  Copyright (c) 2011 Aaron Blasdel. All rights reserved.
//
//  The default Callbacks implement zooming and rotation around the orgin as well as using escape to quit the program
//  Defaults can be overridden by writing replacements and using the set functions 
//  NOTE when overriding the draw callback the preDraw() and postDraw() functions must be used at 
//  the begining/end or the mouse callbacks will not work

#ifndef Vector_Field_Visualizer_GLCanvas_h
#define Vector_Field_Visualizer_GLCanvas_h

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <vector>
#include "GL3.h"

class GLCanvas{
    //Default GLUT callbacks
    static void _resize(int,int);
    static void _display();
    static void _idle();
    static void _keyboard(unsigned char key, int x, int y);
    static void _mouseClick(int button, int state, int x, int y);
    static void _mouseMotion(int x, int y);
    static bool _btnOneDown;
    static bool _btnTwoDown;
    static int _yInitial;
    static int _xInitial;
    static GLfloat _fViewDistance;
    static GLfloat _minViewDist;
    static GLfloat _xRot;
    static GLfloat _yRot;
protected:
//functions designed to be called at the begining and end of a child class's draw callback
    static void preDraw();
    static void postDraw();
    static void reverseRotatation(); //Calling this function will undo the automatic rotation
                                     //this allows placing objects at a static location on the screen
    static GLfloat reverseZoom();    //Returns a static Z value of the current zoomed screen that 
                                     //can be used to place objects in a static position on the screen 
    //GLUT callback assignment fuctions
    void setResizeCallback(void (*callback)(int,int));
    void setDisplayCallback(void (*callback)());
    void setIdleCallback(void (*callback)());
    void setKeyboardCallback(void (*callback)(unsigned char key, int,int));
    void setmouseClickCallback(void (*callback)(int,int,int,int));
    void setMouseMotionCallback(void (*callback)(int,int));
public:
//setup Canvas
    GLCanvas();
    void initilize(int argc, char ** argv,string = "Default GLCanvas Window");
//starts the GLUT Main loop
    void Launch();
};

#endif

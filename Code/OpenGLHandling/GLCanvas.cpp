//
//  GLCanvas.cpp
//  Vector Field Visualizer
//
//  Created by Aaron Blasdel on 12/13/11.
//  Copyright (c) 2011 Aaron Blasdel. All rights reserved.
//

#include <iostream>
#include "GLCanvas.h"

//Initilization of static member functions for use in default callbacks
GLfloat GLCanvas::_xRot=0.0;
GLfloat GLCanvas::_yRot=0.0;
GLfloat GLCanvas::_minViewDist = 3.0;
GLfloat GLCanvas::_fViewDistance = 3 * _minViewDist;
bool GLCanvas::_btnOneDown=false;
bool GLCanvas::_btnTwoDown=false;
int GLCanvas::_yInitial=0;
int GLCanvas::_xInitial=0;

GLCanvas::GLCanvas()
{
}

void GLCanvas::initilize(int argc, char ** argv, string title)
{
    // Sets up a simple window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(1280,800);
    glutCreateWindow(title.c_str());
        
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // Create texture for cube; load marble texture from file and bind it
    
    
    // Setup default callbacks
    glutIdleFunc(_idle);
    glutDisplayFunc(_display);
    glutReshapeFunc(_resize);
    glutKeyboardFunc (_keyboard);
    glutMouseFunc (_mouseClick);
    glutMotionFunc (_mouseMotion);
    
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    static float _lightPos[4] = { 10, 10, 100, 1 };  // Position of light
    // Set up the stationary light
    glLightfv(GL_LIGHT0, GL_POSITION, _lightPos);
}

void GLCanvas::setResizeCallback(void (*callback)(int,int))
{
    glutReshapeFunc(callback);
}

void GLCanvas::setDisplayCallback(void (*callback)())
{
    glutDisplayFunc(callback);
}

void GLCanvas::setIdleCallback(void (*callback)())
{
    glutIdleFunc(callback);
}

void GLCanvas::setKeyboardCallback(void (*callback)(unsigned char key, int,int))
{
    glutKeyboardFunc(callback);
}

void GLCanvas::setmouseClickCallback(void (*callback)(int,int,int,int))
{
    glutMouseFunc(callback);
}

void GLCanvas::setMouseMotionCallback(void (*callback)(int,int))
{
    glutMotionFunc(callback);
}


void GLCanvas::Launch()
{
    glutMainLoop();
}

void GLCanvas::_keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:             // ESCAPE quits the program
            exit (0);
            break;
    }
}

void GLCanvas::_resize(int w,int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.1, 0.1, -float(h)/(10.0*float(w)), float(h)/(10.0*float(w)), 0.2, 9999999.0);
    //    int _nearPlane=1;
    //    int _farPlane=1000;
    //    gluPerspective(65.0, (float)w / h, _nearPlane, _farPlane);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();}


void GLCanvas::_idle()
{
    _display();
}

void GLCanvas::_display()
{
    preDraw();
    
    postDraw();
}

void GLCanvas::_mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        _btnOneDown = (state == GLUT_DOWN) ? true : false;
        if (state==GLUT_DOWN) {
            _xInitial = x;
            _yInitial = y;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        _btnTwoDown = (state == GLUT_DOWN) ? true : false;
        if (state==GLUT_DOWN) {
            _yInitial = y - 3 * _fViewDistance;
        }
    }
}

void GLCanvas::_mouseMotion(int x, int y)
{
    if (_btnOneDown)
    {   //rotate code
        _xRot = x - _xInitial;
        _yRot = y - _yInitial;
        glutPostRedisplay();
    }
    else if (_btnTwoDown)
    {   //zoom code
        _fViewDistance = (y - _yInitial) / 3.0;
        if (_fViewDistance < _minViewDist )
            _fViewDistance = _minViewDist;
        glutPostRedisplay();
    }
}

void GLCanvas::preDraw()
{   //This function MUST be called at the beginning of any draw callback
    //clear the screen and the draw matrix
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //position the camera
    gluLookAt(0, 0, -_fViewDistance, 0, 0, -1, 0, 1, 0);
    glRotatef(-_yRot, 1.f, 0.f, 0.f);/* orbit the X axis */
    glRotatef( _xRot, 0.f, 1.f, 0.f);/* orbit the Y axis */
        
    //Set to modelview so we can draw
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
}

void GLCanvas::postDraw()
{   //This function MUST be called at the end of any draw callback
    glPopMatrix();
    glutSwapBuffers();
}

void GLCanvas::reverseRotatation()
{
    glRotatef(-_xRot, 0.f, 1.f, 0.f);/* orbit the Y axis */
    glRotatef( _yRot, 1.f, 0.f, 0.f);/* orbit the X axis */
}

GLfloat GLCanvas::reverseZoom()
{   //returns the current Z value of the zoomed screen
     return 3*_minViewDist-_fViewDistance;
}


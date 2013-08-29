//
//  DataCanvas.cpp
//  Vector Field Visualizer
//
//  Created by Aaron Blasdel on 12/16/11.
//  Copyright (c) 2011 Aaron Blasdel. All rights reserved.
//

#include <iostream>
#include "DataCanvas.h"

VectorField DataCanvas::_theField; //static member initilization

void DataCanvas::DrawCallback()
{   //Overides callback to draw the field and maintains the Mouse callback functionality
    preDraw();
    _theField.draw();
    
    reverseRotatation();
    //position and print Instructions related to the keyboard input
    char captions[7][100];
    sprintf (captions[0], "Vectorfield interaction instructions"); 
    sprintf (captions[1], "------------------------------------"); 
    sprintf (captions[2], "- and + : remove/add particles"); 
    sprintf (captions[3], "< and > : decrease/increase speed modifier"); 
    sprintf (captions[4], "[ and ] : previous/next vectorfield"); 
    sprintf (captions[5], "L Mouse : rotate scene"); 
    sprintf (captions[6], "R Mouse : zoom scene"); 
    for (int captionsindex=0; captionsindex<7; captionsindex++) {
        //prints each caption moving down one line (-0.1F) for each new caption
        // the z position reverses the GLCanvas
        glRasterPos3f (-2.60F, -2.10F-0.1F*float(captionsindex),reverseZoom()); 
        for (unsigned int i = 0; i < strlen (captions[captionsindex]); i++) 
            glutBitmapCharacter (GLUT_BITMAP_HELVETICA_10, captions[captionsindex][i]); 
    }
    postDraw();
}

void DataCanvas::IdleCallback()
{   //animates _theField and then asks GLUT to redisplay
    _theField.moveParticles();
    glutPostRedisplay();
}

void DataCanvas::KeyboardCallback(unsigned char key, int x, int y)
{   //fully overrides keyboard callback
    switch (key)
    {
        case 27:            //Esc quits the program
            exit (0);
            break;
        case '=':
        case '+':
            _theField.addParticle();
            break;
        case '-':
        case '_':
            _theField.popParticle();
            break;
        case '[':
        case '{':
            _theField.prevFile();
            break;
        case ']':
        case '}':
            _theField.nextFile();
            break;
//        case 'p':
//        case 'P':
//            _theField.toggleDrawMode();
//            break;
        case '>':
        case '.':
            _theField.incParticleSpeed();
            break;
        case '<':
        case ',':
            _theField.decParticleSpeed();
            break;
    }
}

void DataCanvas::initilize(int argc, char ** argv,string title)
{   //calls parents initialize to set things up and then overrides relevent callbacks
    GLCanvas::initilize(argc,argv,title);
    setIdleCallback(IdleCallback);
    setDisplayCallback(DrawCallback);
    setKeyboardCallback(KeyboardCallback);
}



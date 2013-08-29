
#ifndef _GL3_H
#define _GL3_H

//
//  ============================================================
//
//			GL3.h
//
//		Wrappers for 3d OpenGL functions
//
//
//  ============================================================
//
//
//      Copyright (C) 1997
//
//                      Professor Kenneth I. Joy
//                      Computer Science Department
//                      University of California
//                      Davis, CA  95616
//
//      Permission is granted to use at your own risk and
//      distribute this software in source and binary forms
//      provided the above copyright notice and this paragraph
//      are preserved on all copies.  This software is provided
//      "as is" with no express or implied warranty.
//
//
//  ============================================================
//
//  Modified by Aaron Blasdel to work in the 21st century
//
//  ============================================================
//

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "Point.h"
#include "aVector.h"
#include "Color.h"
//#include "Transformation.h"

using namespace std;

   void 		glColor3d ( const Color& ) ;

   void 		glVertex3d ( const Point& ) ;

   void 		glRotated ( const double, const aVector& ) ;

   void 		glTranslated ( const aVector& ) ;

   void 		glNormal3d ( const aVector& ) ;

//   void 		glMultMatrixd ( const Transformation& ) ;

#endif


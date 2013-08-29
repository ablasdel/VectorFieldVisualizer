
//
//  ============================================================
//
//		GL3 -- 3d GL commands
//
//  ============================================================
//
//
// 	Copyright (C) 1997
//
//			Professor Kenneth I. Joy
//			Computer Science Department
//			University of California
//			Davis, CA  95616
//
// 	Permission is granted to use at your own risk and 
//	distribute this software in source and binary forms 
//	provided the above copyright notice and this paragraph 
//	are preserved on all copies.  This software is provided 
//	"as is" with no express or implied warranty.
//
//
//  ============================================================
//
//  Modified by Aaron Blasdel to work in the 21st century
//
//  ============================================================
//

#include <stdlib.h>
#include <cmath>
//#include <strings.h>
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "GL3.h"

#define        TRUE            1
#define        FALSE           0

//
// ============================================================
//
//		glColor3d
//
// ============================================================
//

void glColor3d ( const Color& c )

   {
      glColor3d ( c.red(), c.green(), c.blue() ) ;
   }


//
// ============================================================
//
//		glVertex3d
//
// ============================================================
//

void glVertex3d ( const Point& p )

   {
      glVertex3d ( p.x(), p.y(), p.z() ) ;
   }


//
// ============================================================
//
//		glRotated
//
// ============================================================
//

void glRotated ( const double angle, const aVector& v )

   {
      double a = angle ;
      glRotated ( a, v.x(), v.y(), v.z() ) ;
   }

//
// ============================================================
//
//		glTranslated
//
// ============================================================
//

void glTranslated ( const aVector& v )

   {
      glTranslated ( v.x(), v.y(), v.z() ) ;
   }

//
// ============================================================
//
//		glNormal3d
//
// ============================================================
//

void glNormal3d ( const aVector& v )

   {
      glNormal3d ( v.x(), v.y(), v.z() ) ;
   }


//
// ============================================================
//
//		glMultMatrixd
//
// ============================================================
//

/*void glMultMatrixd ( const Transformation& t )

   {
      double trans[4][4] ;

      for ( int i = 0 ; i < 4 ; i++ ) {
	 for ( int j = 0 ; j < 4 ; j++ ) {
	    trans[i][j] = t.matrix ( i, j ) ;
	    }
	 }

      glMultMatrixd ( (const double *) trans ) ;
   }
*/

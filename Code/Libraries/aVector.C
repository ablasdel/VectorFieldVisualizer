
//
// ============================================================
//
//                      aVector
//
// ============================================================
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

#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "GL3.h"
#include "aVector.h"
#include "Material.h"

#define		TRUE		1 
#define		FALSE		0


/*
   ==========================================================

	       CONSTRUCTORS, DESTRUCTOR

   ==========================================================
*/

aVector :: aVector ()

   {
      _x = 0.0 ;
      _y = 0.0 ;
      _z = 0.0 ;
   }

aVector :: aVector ( const double x, const double y, const double z )

   {
      _x = x ;
      _y = y ;
      _z = z ;
   }

aVector :: aVector ( const aVector& v ) 

   {
      _x = v._x ;
      _y = v._y ;
      _z = v._z ;
   }

aVector :: ~aVector () { }
      

/*
   ==========================================================

	       OPERATOR=

   ==========================================================
*/

aVector& aVector :: operator= ( const aVector& v ) 

   {
      if ( this == &v ) return ( *this ) ;

      _x = v._x ;
      _y = v._y ;
      _z = v._z ;

      return ( *this ) ;
   }

/*
   ==========================================================

	       OUTPUT

   ==========================================================
*/

ostream& operator<< ( ostream& co, const aVector& v )

   {
      return v.output ( co ) ;
   }

ostream& aVector :: output ( ostream& co, const int indent ) const 

   {
      for ( int i = 0 ; i < indent ; i++ ) co << " " ;

      co << "< " 
	 << _x << ", " 
	 << _y << ", " 
	 << _z << " >" ;

      return ( co ) ;
   }

/*
   ==========================================================

	       INPUT

   ==========================================================
*/

istream& operator>> ( istream& ci, aVector& v )

   {
      double x = 0.0 ;
      double y = 0.0 ;
      double z = 0.0 ;

      ci >> x >> y >> z ;

      v = aVector ( x, y, z ) ;

      return ci ;
   }

/*
   ==========================================================

	       COMPARISON OPERATIONS

   ==========================================================
*/

int operator== ( const aVector& v1, const aVector& v2 ) 

   {
      if ( ( v1._x == v2._x ) &&
           ( v1._y == v2._y ) &&
           ( v1._z == v2._z ) )
	    return ( TRUE ) ;
	 else
	    return ( FALSE ) ;
   }

int operator!= ( const aVector& v1, const aVector& v2 ) 

   {
      if ( ( v1._x != v2._x ) ||
           ( v1._y != v2._y ) ||
           ( v1._z != v2._z ) )
	    return ( TRUE ) ;
	 else
	    return ( FALSE ) ;
   }

/*
   ==========================================================

	       ARITHMETIC OPERATIONS

   ==========================================================
*/

aVector operator+ ( const aVector& v1, const aVector& v2 ) 

   {
      aVector vv ;

      vv._x = v1._x + v2._x ;
      vv._y = v1._y + v2._y ;
      vv._z = v1._z + v2._z ;

      return ( vv ) ;
   }

aVector operator- ( const aVector& v1, const aVector& v2 ) 

   {
      aVector vv ;

      vv._x = v1._x - v2._x ;
      vv._y = v1._y - v2._y ;
      vv._z = v1._z - v2._z ;

      return ( vv ) ;
   }

aVector operator- ( const aVector& v ) 

   {
      aVector vv ;

      vv._x = - v._x ;
      vv._y = - v._y ;
      vv._z = - v._z ;

      return ( vv ) ;
   }

aVector operator* ( const double& c, const aVector& v ) 

   {
      aVector vv ;

      vv._x = c * v._x ;
      vv._y = c * v._y ;
      vv._z = c * v._z ;

      return ( vv ) ;
   }

aVector operator* ( const aVector& v, const double& c ) 

   {
      aVector vv ;

      vv._x = c * v._x ;
      vv._y = c * v._y ;
      vv._z = c * v._z ;

      return ( vv ) ;
   }

aVector operator/ ( const aVector& v, const double& c ) 

   {
      aVector vv ;

      vv._x = v._x / c ;
      vv._y = v._y / c ;
      vv._z = v._z / c ;

      return ( vv ) ;
   }

aVector cross ( const aVector& v1, const aVector& v2 ) 

   {
      aVector vv ;

      vv._x = v1._y * v2._z - v1._z * v2._y ;
      vv._y = - v1._x * v2._z + v1._z * v2._x ;
      vv._z = v1._x * v2._y - v1._y * v2._x ;

      return ( vv ) ;
   }

aVector& aVector :: operator+= ( const aVector& v ) 

   {
      _x += v._x ;
      _y += v._y ;
      _z += v._z ;

      return *this ;
   }

aVector& aVector :: operator-= ( const aVector& v ) 

   {
      _x -= v._x ;
      _y -= v._y ;
      _z -= v._z ;

      return *this ;
   }

aVector& aVector :: operator*= ( const double& c ) 

   {
      _x *= c ;
      _y *= c ;
      _z *= c ;

      return *this ;
   }

aVector& aVector :: operator/= ( const double& c ) 

   {
      _x /= c ;
      _y /= c ;
      _z /= c ;

      return *this ;
   }

/*
   ==========================================================

	       NORMALIZE

   ==========================================================
*/

void aVector :: normalize ()  

   {
      double l =  length () ;

      _x = _x / l ;
      _y = _y / l ;
      _z = _z / l ;
   }

/*
   ==========================================================

	       LENGTH

   ==========================================================
*/

double aVector :: length ()  const

   {
      double		l ;

      l =  sqrt ( _x * _x + _y * _y + _z * _z ) ;
      return ( l ) ;
   }

/*
   ==========================================================

	       DOT

   ==========================================================
*/

double dot ( const aVector& v1, const aVector& v2 ) 

   {
      double		d ;

      d =  v1._x * v2._x + v1._y * v2._y + v1._z * v2._z ;

      return ( d ) ;
   }


/*
   ==========================================================

               ANGLE_BETWEEN

   ==========================================================
*/

double angle_between ( const aVector& v1, const aVector& v2 )

   {
      double d = dot ( v1, v2 ) ;

      double l1 = v1.length() ;
      double l2 = v2.length() ;

      if ( ( l1 < 1.0e-8 ) || ( l2 < 1.0e-8 ) ) return ( M_PI ) ;

      return ( acos ( d / ( l1 * l2 ) ) ) ;
   }

/*
   ==========================================================

	       DRAW

   ==========================================================
*/

void aVector :: Draw ( const aMaterial& mat, const double thick )  const

   {
      DrawFromPoint ( mat, ZeroPoint, thick ) ;
   }


/*
   ==========================================================

	       DRAWFROMPOINT

   ==========================================================
*/
void aVector :: DrawFromPoint ( const aMaterial& mat, 
		      const Point& anchor,
		      const double thick )  const

   {
      double len = length() ;
      double theta = atan2 ( z(), x() ) * 180.0 / M_PI ;
      double phi = atan2 ( y(), sqrt ( x() * x() + z() * z() ) ) 
					* 180.0 / M_PI ;

      glPushMatrix() ;

	 glTranslated ( anchor - ZeroPoint ) ;

	 glPushMatrix() ;

	   glRotated ( -theta, YVector ) ;
	   glRotated ( phi, ZVector ) ;
	   glScaled ( len, thick, thick ) ;

	    for ( int i = 0 ; i < 4 ; i++ ) {
	      mat.GL() ;
	       glBegin ( GL_POLYGON ) ;
		  glNormal3d ( 0.0, 0.0, 1.0 ) ;
		  glVertex3d ( 0.0, 0.5, 0.5 ) ;
		  glVertex3d ( 0.85, 0.5, 0.5 ) ;
		  glVertex3d ( 0.85, -0.5, 0.5 ) ;
		  glVertex3d ( 0.0, -0.5, 0.5 ) ;
	       glEnd () ;

	       glBegin ( GL_POLYGON ) ;
		  glNormal3d ( -1.0, 0.0, 0.0 ) ;
		  glVertex3d ( 0.85, 1.0, 1.0 ) ;
		  glVertex3d ( 0.85, 0.5, 0.5 ) ;
		  glVertex3d ( 0.85, -0.5, 0.5 ) ;
		  glVertex3d ( 0.85, -1.0, 1.0 ) ;
	       glEnd () ;

	       glBegin ( GL_POLYGON ) ;
		  aVector p1 = aVector ( 0.85, -1.0, 1.0 ) ;
		  aVector p2 = aVector ( 0.85, 1.0, 1.0 ) ;
		  aVector p3 = aVector ( 1.0, 0.0, 0.0 ) ;
		  aVector v1 = p1 - p3 ;
		  aVector v2 = p2 - p3 ;
		  aVector n = cross ( v1, v2 ) ;
		  n.normalize() ;

		  glNormal3d ( -n ) ;
		  glVertex3d ( p1.x(), p1.y(), p1.z() ) ;
		  glVertex3d ( p2.x(), p2.y(), p2.z() ) ;
		  glVertex3d ( p3.x(), p3.y(), p3.z() ) ;
	       glEnd () ;

	       glRotated ( 90.0, XVector ) ;
	       }

      glPopMatrix() ;
      glPopMatrix() ;
   }


//
// ============================================================
//
//            PROJECT_TO_SPHERE
//
// ============================================================
//

aVector aVector::project_to_sphere ( const Point & p, const double radius ) 

{
    double z ;
    
    double d = sqrt ( p.x() * p.x() + p.y() * p.y() ) ;
    
    if ( d < radius * M_SQRT1_2 ) {
	    z = sqrt ( radius * radius - d * d ) ;
    }
    else {
	    double t = radius / M_SQRT2 ;
	    z = t * t / d ;
    }
    
    return ( aVector ( p.x(), p.y(), z ) ) ;
}


//
//  ============================================================
//
//                        Point.C
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
//
//  Modified by Aaron Blasdel to work in the 21st century
//
//  ============================================================
//


//#include <stdlib>
#include <cmath>
//#include <strings>
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "Point.h"

#define		TRUE		1 
#define		FALSE		0

using namespace std;
/*
   ==========================================================

	       CONSTRUCTORS, DESTRUCTOR

   ==========================================================
*/

Point :: Point ()

   {
      _x = 0.0 ;
      _y = 0.0 ;
      _z = 0.0 ;
   }

Point :: Point ( const double x, const double y, const double z )

   {
      _x = x ;
      _y = y ;
      _z = z ;
   }

Point :: Point ( const Point& p ) 

   {
      _x = p._x ;
      _y = p._y ;
      _z = p._z ;
   }

Point :: ~Point () { }
      

/*
   ==========================================================

	       OPERATOR=

   ==========================================================
*/

Point& Point :: operator= ( const Point& p ) 

   {
      if ( this == &p ) return ( *this ) ;

      _x = p._x ;
      _y = p._y ;
      _z = p._z ;

      return ( *this ) ;
   }

/*
   ==========================================================

	       OUTPUT

   ==========================================================
*/

ostream& operator<< ( ostream& co, const Point& p )

   {
      return p.output( co ) ;
   }

/*
   ==========================================================

	       OUTPUT

   ==========================================================
*/

ostream& Point ::output ( ostream& co, const int indent ) const

   {
      for ( int i = 0 ; i < indent ; i++ ) co << " " ;

      co << "( " << _x << ", " << _y << ", " << _z << " )" ;

      return ( co ) ;
   }

/*
   ==========================================================

	       INPUT

   ==========================================================
*/

istream& operator>> ( istream& ci, Point& p )

   {
      double x = 0.0 ;
      double y = 0.0 ;
      double z = 0.0 ;

      ci >> x >> y >> z ;

      p = Point ( x, y, z ) ;

      return ci ;
   }
/*
   ==========================================================

	       COMPARISON OPERATIONS

   ==========================================================
*/

int operator== ( const Point& p1, const Point& p2 ) 

   {
      if ( ( p1._x == p2._x ) &&
           ( p1._y == p2._y ) &&
           ( p1._z == p2._z ) )
	    return ( TRUE ) ;
	 else
	    return ( FALSE ) ;
   }

int operator!= ( const Point& p1, const Point& p2 ) 

   {
      if ( ( p1._x != p2._x ) ||
           ( p1._y != p2._y ) ||
           ( p1._z != p2._z ) )
	    return ( TRUE ) ;
	 else
	    return ( FALSE ) ;
   }

/*
   ==========================================================

	       ARITHMETIC OPERATIONS

   ==========================================================
*/

Point operator+ ( const Point& p1, const aVector& p2 ) 

   {
      Point pp ;

      pp._x = p1._x + p2.x() ;
      pp._y = p1._y + p2.y() ;
      pp._z = p1._z + p2.z() ;

      return ( pp ) ;
   }

Point operator+ ( const aVector& p2, const Point& p1 ) 

   {
      Point pp ;

      pp._x = p1._x + p2.x() ;
      pp._y = p1._y + p2.y() ;
      pp._z = p1._z + p2.z() ;

      return ( pp ) ;
   }

aVector operator- ( const Point& p1, const Point& p2 ) 

   {
      aVector vv ( p1._x - p2._x, p1._y - p2._y, p1._z - p2._z ) ;
      return ( vv ) ;
   }

Point operator- ( const Point& p, const aVector& v ) 

   {
      Point pp ( p._x - v.x(), p._y - v.y(), p._z - v.z() ) ;
      return ( pp ) ;
   }

Point operator- ( const Point& p ) 

   {
      Point pp ;

      pp._x = -p._x ;
      pp._y = -p._y ;
      pp._z = -p._z ;

      return ( pp ) ;
   }

Point operator- ( const Point& p ,const double d) 

   {
      Point pp ;

      pp._x = p._x-d ;
      pp._y = p._y-d ;
      pp._z = p._z-d ;

      return ( pp ) ;
   }

Point& Point :: operator+= ( const aVector& v )

   {
      _x += v.x() ;
      _y += v.y() ;
      _z += v.z() ;

      return ( *this ) ;
   }

Point& Point :: operator-= ( const aVector& v )

   {
      _x -= v.x() ;
      _y -= v.y() ;
      _z -= v.z() ;

      return ( *this ) ;
   }



/*
   ==========================================================

	       AFFINE

   ==========================================================
*/

Point affine ( const Point& p1, const Point& p2, const double t ) 

   {
      Point p ;

      p._x = p1._x + t * ( p2._x - p1._x ) ;
      p._y = p1._y + t * ( p2._y - p1._y ) ;
      p._z = p1._z + t * ( p2._z - p1._z ) ;

      return ( p ) ;
   }

Point affine ( const Point& p1, 
	       const Point& p2, 
	       const Point& p3, 
	       const double a1,
	       const double a2,
	       const double a3 )

   {
      Point p ;

      p._x = a1 * p1._x + a2 * p2._x + a3 * p3._x ;
      p._y = a1 * p1._y + a2 * p2._y + a3 * p3._y ;
      p._z = a1 * p1._z + a2 * p2._z + a3 * p3._z ;

      return ( p ) ;
   }

Point affine ( const Point& p1, 
	       const Point& p2, 
	       const Point& p3, 
	       const Point& p4, 
	       const double a1,
	       const double a2,
	       const double a3,
	       const double a4 )

   {
      Point p ;

      p._x = a1 * p1._x + a2 * p2._x + a3 * p3._x + a4 * p4._x ;
      p._y = a1 * p1._y + a2 * p2._y + a3 * p3._y + a4 * p4._y ;
      p._z = a1 * p1._z + a2 * p2._z + a3 * p3._z + a4 * p4._z ;

      return ( p ) ;
   }


/*
   ==========================================================

	       MIDPOINT

   ==========================================================
*/

Point midpoint ( const Point& p1, const Point& p2 )

   {
      return ( affine ( p1, p2, 0.5 ) ) ;
   }


/*
   ==========================================================

	       AVERAGE

   ==========================================================
*/

Point average ( Point *p, const int n ) 

   {
      double xsum = 0.0 ;
      double ysum = 0.0 ;
      double zsum = 0.0 ;

      double weight = 1.0 / ( (double) n ) ;

      for ( int i = 0 ; i < n ; i++ ) {
	 xsum += weight * p[i].x() ;
	 ysum += weight * p[i].y() ;
	 zsum += weight * p[i].z() ;
	 }

      return ( Point ( xsum, ysum, zsum ) ) ;
   }


Point average ( const Point& p1,
		const Point& p2,
		const Point& p3 ) 

   {
      Point pts[3] ;
      pts[0] = p1 ;
      pts[1] = p2 ;
      pts[2] = p3 ;

      return ( average ( pts, 3 ) ) ;
   }

Point average ( const Point& p1,
		const Point& p2,
		const Point& p3,
		const Point& p4 ) 

   {
      Point pts[4] ;
      pts[0] = p1 ;
      pts[1] = p2 ;
      pts[2] = p3 ;
      pts[3] = p4 ;

      return ( average ( pts, 4 ) ) ;
   }

/*
   ==========================================================

               Draw

   ==========================================================
*/

void Point :: Draw ( const aMaterial& mat, 
		     const double radius,
		     const int segments ) const

   {
      glPushMatrix() ;

	 mat.GL() ;
	 glTranslated ( x(), y(), z() ) ;
	 GLUquadricObj *obj = gluNewQuadric() ;
	 gluSphere ( obj, radius, segments, segments ) ;

      glPopMatrix() ;
   }


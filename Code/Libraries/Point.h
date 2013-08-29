
#ifndef _POINT_H
#define _POINT_H

//
//  ============================================================
//
//                        Point.h
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


#include <iostream>
#include "aVector.h"
#include "Material.h"

using namespace std;

class	Point {

   private :
	
      double		_x, _y, _z ;

   public :

			//  Constructors

      Point () ;

      Point ( const double, 
	      const double = 0.0, 
	      const double = 0.0 ) ;

			//  Copy Constructor

      Point ( const Point& ) ;

			//  Destructor

      virtual ~Point () ;

			//  Assignment

      Point& operator= ( const Point& ) ;

			//  Input/Output

      friend ostream& operator<< ( ostream&, const Point& ) ;
      ostream& output ( ostream&, const int = 0 ) const ;
      friend istream& operator>> ( istream&, Point& ) ;

			//  Comparison

      friend int operator== ( const Point&, const Point& ) ;
      friend int operator!= ( const Point&, const Point& ) ;

			//  Arithmetic Operations

      friend Point operator+ ( const Point&, const aVector& ) ;
      friend Point operator+ ( const aVector&, const Point& ) ;
      friend aVector operator- ( const Point&, const Point& ) ;
      friend Point operator- ( const Point&, const aVector& ) ;
      friend Point operator- ( const Point& ) ;
      friend Point operator- ( const Point& p ,const double d) ;

      Point& operator+= ( const aVector& ) ;
      Point& operator-= ( const aVector& ) ;

			//  Affine Combinations

      friend Point affine ( const Point&, 
			    const Point&, 
			    const double ) ;

      friend Point affine ( const Point&, 
			    const Point&, 
			    const Point&, 
			    const double,
			    const double,
			    const double ) ;

      friend Point affine ( const Point&, 
			    const Point&, 
			    const Point&, 
			    const Point&, 
			    const double,
			    const double,
			    const double,
			    const double ) ;

      friend Point average ( Point *, const int ) ;
      friend Point average ( const Point&, 
			     const Point&, 
			     const Point& ) ;
      friend Point average ( const Point&, 
			     const Point&, 
			     const Point&, 
			     const Point& ) ;

      friend Point midpoint ( const Point&, const Point& ) ;

			//  Access Functions

      double x () const { return _x ; } ;
      double y () const { return _y ; } ;
      double z () const { return _z ; } ;
      void xyz(double x,double y, double z)
{
 _x=x;
 _y=y;
 _z=z;
}

			//  Drawing

      void Draw ( const aMaterial&, 
		  const double = 0.01,
		  const int = 8 ) const ;

   } ;

const Point ZeroPoint ( 0.0, 0.0, 0.0 ) ;
#endif




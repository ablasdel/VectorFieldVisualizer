
#ifndef _AVECTOR_H
#define _AVECTOR_H

//
//  ============================================================
//
//                        aVector.h
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


#include "Material.h"

using namespace std;

class Point ;

class aVector {

   private :
	
      double		_x, _y, _z ;

   public :

      aVector () ;

      aVector ( const double, 
	       const double = 0.0, 
	       const double = 0.0 ) ;

      aVector ( const aVector& ) ;

      virtual ~aVector () ;

      aVector& operator= ( const aVector& ) ;

    
      friend ostream& operator<< ( ostream&, const aVector& ) ;
      ostream& output ( ostream&, const int = 0 ) const ;
      friend istream& operator>> ( istream&, aVector& ) ;

      friend int operator== ( const aVector&, const aVector& ) ;
      friend int operator!= ( const aVector&, const aVector& ) ;

      friend aVector operator+ ( const aVector&, const aVector& ) ;
      friend aVector operator- ( const aVector&, const aVector& ) ;
      friend aVector operator- ( const aVector& ) ;
      friend aVector operator* ( const double&, const aVector& ) ;
      friend aVector operator* ( const aVector&, const double& ) ;
      friend aVector operator/ ( const aVector&, const double& ) ;

      aVector& operator+= ( const aVector& ) ;
      aVector& operator-= ( const aVector& ) ;
      aVector& operator*= ( const double& ) ;
      aVector& operator/= ( const double& ) ;

      friend double dot ( const aVector&, const aVector& ) ;

      friend aVector cross ( const aVector&, const aVector& ) ;

      void normalize () ;

      double length () const ;

      friend double angle_between ( const aVector&, const aVector& ) ;

      double x () const { return _x ; } ;
      double y () const { return _y ; } ;
      double z () const { return _z ; } ;

      aVector project_to_sphere ( const Point& , const double ) ;

		// Drawing

      void Draw ( const aMaterial&, 
		  const double = 0.02 ) const ;

      void DrawFromPoint ( const aMaterial&, 
			   const Point&,
			   const double = 0.02 ) const ;

   } ;

const aVector ZeroVector ( 0.0, 0.0, 0.0 ) ;
const aVector XVector ( 1.0, 0.0, 0.0 ) ;
const aVector YVector ( 0.0, 1.0, 0.0 ) ;
const aVector ZVector ( 0.0, 0.0, 1.0 ) ;

#include "Point.h"

#endif




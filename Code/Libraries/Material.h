
#ifndef _MATERIAL_H
#define _MATERIAL_H


//
//  ============================================================
//
//                  Material
//
//  ============================================================
//
//
//      Copyright (C) 1992,1993,1994
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


#include "Color.h"

using namespace std;

class	aMaterial {

  private :

      Color			_ambient ;
      Color			_diffuse ;
      Color			_specular ;

      double		_glossiness ;

   public :

		//  Constructors

      aMaterial () ;

		//  The simple constructor, designed to let you
		//     just specify a color and have the other
		//     parameters all default.

      aMaterial ( const Color&, 
		     const double = 0.2,   // specular component is gray
		     const double = 50.0 ) ;

		//  This constructor takes all parameters.

      aMaterial ( const Color&, 
		 const Color&, 
		 const Color&, 
		 const double ) ;

		//  Copy Constructor

      aMaterial ( const aMaterial& p ) ;

		//  Destructor

      virtual ~aMaterial () ;

		//  Assignment

      aMaterial& operator= ( const aMaterial& p ) ;

		//  Input, Output

      friend ostream& operator<< ( ostream&, const aMaterial& ) ;
      ostream& output ( ostream& ) const ;

		//  Access Functions ;

      Color ambient () const { return _ambient ; } ;
      Color diffuse () const { return _diffuse ; } ;
      Color specular () const { return _specular ; } ;
      double glossiness () const { return _glossiness ; } ;

      void set_ambient ( const Color& color ) { _ambient = color ; } ;
      void set_diffuse ( const Color& color ) { _diffuse = color ; } ;

      void set_specular ( const double spec ) 
		{ _specular = Color ( spec, spec, spec ) ; } ;
      void set_specular ( const Color& c ) 
		{ _specular = c ; } ;

      void set_glossiness ( const double facets ) 
		{ _glossiness = facets ; } ;

		//  This member function executes all the OpenGL
		//    commands to allow this material to be assigned
		//    to an object.

      void GL() const ;

  } ;

const aMaterial WhiteMaterial ( White ) ;
const aMaterial YellowMaterial ( Yellow ) ;
const aMaterial GreenMaterial ( Green ) ;
const aMaterial RedMaterial ( Red ) ;
const aMaterial DefaultMaterial ( Gray60 ) ;

#endif

//
//  ============================================================
//
//                  Material.C
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


/*
   ============================================================

			MATERIAL

   ============================================================
*/


#include <stdlib.h>
#include <cmath>
//#include <strings>
#include <iostream>
#include <OpenGL/gl.h>
#include "Color.h"
#include "Material.h"

/*
   ============================================================

		CONSTRUCTOR, DESTRUCTOR

   ============================================================
*/

aMaterial :: aMaterial ()

   {
      _ambient = Color ( 0.4, 0.4, 0.4 ) ;
      _diffuse = Color ( 0.4, 0.4, 0.4 ) ;
      _specular = Color ( 0.2, 0.2, 0.2 ) ;
      _glossiness = 50.0 ;
   }

aMaterial :: aMaterial ( const Color& diffuse,
			       const double spec,
			       const double gloss )

   {
      _ambient = diffuse ;
      _diffuse = diffuse ;
      _specular = Color ( spec, spec, spec ) ;
      _glossiness = gloss ;
   }

aMaterial :: aMaterial ( const Color& ambient,
		       const Color& diffuse,
		       const Color& spec,
		       const double gloss )

   {
      _ambient = ambient ;
      _diffuse = diffuse ;
      _specular = spec ;
      _glossiness = gloss ;
   }

aMaterial :: aMaterial ( const aMaterial& p )

   {
      _ambient = p._ambient ;
      _diffuse = p._diffuse ;
      _specular = p._specular ;
      _glossiness = p._glossiness ;
   }

aMaterial :: ~aMaterial () {}


/*
   ============================================================

		OPERATOR=

   ============================================================
*/

aMaterial& aMaterial :: operator= ( const aMaterial& p )

   {
      if ( this == &p ) return ( *this ) ;

      _ambient = p._ambient ;
      _diffuse = p._diffuse ;
      _specular = p._specular ;
      _glossiness = p._glossiness ;

      return ( *this ) ;
   }

/*
   ============================================================

		OUTPUT

   ============================================================
*/

ostream& operator<< ( ostream& co, const aMaterial& s ) 

   {
      return s.output ( co ) ;
   }

ostream& aMaterial :: output ( ostream& co ) const 

   {
      co << "aMaterial ( " 
         << _ambient << ", " 
         << _diffuse << ", " 
         << _specular << ", " 
         << _glossiness << " )" ;

      return ( co ) ;
   }


/*
   ============================================================

		GL Setup

   ============================================================
*/

void aMaterial :: GL () const 

   {
      GLfloat array[4] ;

      array[0] = GLfloat ( _ambient.red() ) ;
      array[1] = GLfloat ( _ambient.green() ) ;
      array[2] = GLfloat ( _ambient.blue() ) ;
      array[3] = 1.0 ;

      glMaterialfv ( GL_FRONT_AND_BACK , GL_AMBIENT , array ) ;

      array[0] = GLfloat ( _diffuse.red() ) ;
      array[1] = GLfloat ( _diffuse.green() ) ;
      array[2] = GLfloat ( _diffuse.blue() ) ;
      array[3] = 1.0 ;

      glMaterialfv ( GL_FRONT_AND_BACK, GL_DIFFUSE, array ) ;

      array[0] = GLfloat ( _specular.red() ) ;
      array[1] = GLfloat ( _specular.green() ) ;
      array[2] = GLfloat ( _specular.blue() ) ;
      array[3] = 1.0 ;

      glMaterialfv ( GL_FRONT_AND_BACK, GL_SPECULAR, array ) ;

      array[0] = 0.0 ;
      array[1] = 0.0 ;
      array[2] = 0.0 ;
      array[3] = 1.0 ;

      glMaterialfv ( GL_FRONT_AND_BACK, GL_EMISSION, array ) ;

      glMaterialf ( GL_FRONT_AND_BACK, GL_SHININESS, GLfloat ( _glossiness ) ) ;
   }


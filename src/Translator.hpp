/*
 * Translator.hpp
 *     Visual tool for moving shapes.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef __TRANSLATOR_HEADER__
#define __TRANSLATOR_HEADER__
#include <cmath>
#include <iostream>
#include <GL/glut.h>
#include "Manipulator.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"



class Translator : public Manipulator {
	
	
	public :
		
		Translator(float x, float y, float z);
		
		void draw() const;
		void use(Scene *scene, const Vector &difference);
	
	
	private:
		
		Translator();
		
		GLUquadricObj *cyl;
};


#endif

/*
 * Translator.hpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef __TRANSLATOR_HEADER__
#define __TRANSLATOR_HEADER__
#include <cmath>
#include <iostream>
#include <GL/glut.h>
#include "Item.hpp"
#include "Manipulator.hpp"
#include "Matrix.hpp"
#include "Scene.hpp"
#include "Vector.hpp"



/**
 * @brief
 *     Tool for moving other items.
 * @ingroup frontend
 */
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

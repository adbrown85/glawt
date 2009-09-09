/*
 * Translator.hpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <vector>
#include "Identifiable.hpp"
#include "Manipulator.hpp"
#include "Matrix.hpp"
#include "Node.hpp"
#include "Scene.hpp"
#include "Selection.hpp"
#include "Shape.hpp"
#include "Translation.hpp"
#include "Vector.hpp"
using std::vector;



/**
 * @brief
 *     Tool for moving shapes.
 * @ingroup frontend
 */
class Translator : public Manipulator {
	
	
	public :
		
		Translator(float x, float y, float z);
		
		void draw() const;
		float findPixelFactor(Scene *scene,
		                      GLuint shapeID);
		void use(Scene *scene,
		         const Vector &movement,
		         GLuint shapeID);
	
	
	private:
		
		Translator();
		
		GLUquadricObj *cone, *disk;
};


#endif

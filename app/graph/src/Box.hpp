/*
 * Box.hpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef __BOX_HPP__
#define __BOX_HPP__
#include <iostream>
#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"



/**
 * @brief
 *     Cube shape that can be drawn by %Display.
 * @ingroup graph
 */
class Box : public Shape {
	
	
	public : 
		
		Box();
		Box(float size);
		
		virtual void draw() const;
		
		void setColor(float r, float g, float b);
	
	
	private:
		
		GLfloat colors[24][3];
		static bool loaded;
		static GLfloat coordinates[24][3], points[24][3];
		static GLubyte indices[24], map[8][3];
		
		void initialize();
		void initializeColors();
		void initializeCoordinates();
		void initializeIndices();
		void initializeMap();
		void initializePoints();
};


#endif

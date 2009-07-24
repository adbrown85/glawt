/*
 * Box.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef BOX_HPP
#define BOX_HPP
#include <iostream>
#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"
using namespace std;



/**
 * @ingroup graph
 * @brief
 *     Cube shape that can be drawn by %Display.
 */
class Box : public Shape {
	
	
	public : 
		
		Box();
		Box(float size);
		virtual void draw() const;
		virtual void print() const;
		void setColor(float r, float g, float b);
	
	
	protected: 
		
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

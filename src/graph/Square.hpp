/*
 * Square.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef SQUARE_HPP
#define SQUARE_HPP
#include <iostream>
#include <GL/glut.h>
#include <sstream>
#include "Shape.hpp"
#include "Vector.hpp"
using namespace std;



/**
 * @ingroup graph
 * @brief
 *     2D square shape that can be drawn by %Display.
 */
class Square : public Shape {
	
	
	public : 
		
		Square(float size,
		       bool inClipSpace=false);
		virtual void draw() const;
		virtual string toString() const;
	
	
	protected: 
		
		bool inClipSpace;
		
		static bool loaded;
		static GLfloat points[4][3];
		static GLubyte indices[4];
		
		void initIndices();
		void initPoints();
};


#endif

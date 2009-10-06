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
#include "Tag.hpp"
#include "Texture.hpp"
using namespace std;



/**
 * @ingroup graph
 * @brief
 *     2D square shape that can be drawn by %Display.
 */
class Square : public Shape {
	
	
	public : 
		
		Square(float size);
		Square(const Tag &tag);
		virtual void draw() const;
	
	
	protected: 
		
		static bool loaded;
		static GLfloat points[4][3];
		static GLubyte indices[4];
		
		virtual void init();
		virtual void initIndices();
		virtual void initPoints();
};


#endif

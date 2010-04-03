/*
 * BoxVBO.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BOXVBO_HPP
#define BOXVBO_HPP
#include <cstdlib>
#include <iostream>
#include "Shape.hpp"
#include "Tag.hpp"
using namespace std;


class BoxVBO : public Shape {
	
	public :
		
		BoxVBO(float size=1.0);
		BoxVBO(const Tag &tag);
		virtual void draw() const;
	
	private:
		
		static bool loaded;
		static GLfloat points[24][3];
		static GLubyte map[8][3];
		static GLuint pointsBuffer, indicesBuffer;
		static GLushort indices[24];
		
		void init();
		void initBuffers();
		void initIndices();
		void initMap();
		void initPoints();
};


#endif

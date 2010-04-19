/*
 * Cube.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CUBE_HPP
#define CUBE_HPP
#include <cstdlib>
#include <iostream>
#include "Program.hpp"
#include "Shape.hpp"
#include "Tag.hpp"
using namespace std;


class Cube : public Shape {
	
	public:
		
		Cube(float size=1.0);
		Cube(const Tag &tag);
		virtual void finalize();
		virtual void draw() const;
	
	private:
		
		int coordsLoc, pointsLoc;
		static bool loaded;
		static int coords2dOffset, coords3dOffset, pointsOffset;
		static GLfloat coords2d[24][3], coords3d[24][3], points[24][3];
		static GLubyte map[8][3];
		static GLuint dataBuffer, indicesBuffer;
		static GLushort indices[24];
		
		void init();
		void initBuffers();
		void initCoords2d();
		void initCoords3d();
		void initIndices();
		void initMap();
		void initPoints();
};


#endif

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
#include "Texture.hpp"
#include "Vector.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief
 *     Cube shape that can be drawn by %Display.
 */
class Box : public Shape {
	
	public : 
		
		Box(float size=1.0);
		Box(const Tag &tag);
		virtual void draw() const;
	
	protected: 
		
		static bool loaded;
		static GLfloat coords[24][3], points[24][3], normals[24][3];
		static GLubyte indices[24], map[8][3];
		
		void init();
		void initCoords();
		void initIndices();
		void initMap();
		void initNormals();
		void initPoints();
};


#endif

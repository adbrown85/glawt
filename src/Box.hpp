/*
 * Box.hpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef BOX_HPP
#define BOX_HPP
#include <iostream>
#include <GL/glut.h>
#include "Item.hpp"
#include "Vector.hpp"



class Box : public Item {
	
	
	public : 
		
		Box();
		Box(float size);
		
		virtual void draw() const;
		
		void setColor(float r, float g, float b);
	
	
	private:
		
		float size;
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

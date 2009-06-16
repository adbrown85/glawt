/*
 * Outline.hpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef OUTLINE_HPP
#define OUTLINE_HPP
#include <iostream>
#include <GL/glut.h>
#include "Item.hpp"
#include "Vector.hpp"



class Outline : public Item {
	
	
	public : 
		
		Outline(float size);
		
		virtual void draw() const;
		
		void setColor(float r, float g, float b);
		void setSize(float size);
	
	
	private:
		
		float color[3];
		static bool loaded;
		static GLfloat points[24][3];
		static GLubyte indices[24], map[8][3];
		
		void initialize();
		void initializeIndices();
		void initializeMap();
		void initializePoints();
};


#endif

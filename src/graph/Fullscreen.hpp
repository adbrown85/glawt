/*
 * Fullscreen.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef FULLSCREEN_HPP
#define FULLSCREEN_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include "Drawable.hpp"
#include "Node.hpp"
#include "Tag.hpp"



class Fullscreen : public Node,
                   public Drawable {
	
	
	public:
		
		Fullscreen();
		Fullscreen(const Tag &tag);
		virtual void draw() const;
	
	
	protected:
		
		static bool loaded;
		static GLfloat coordinates[4][3];
		static GLfloat points[4][3];
		static GLubyte indices[4];
		
		virtual void init();
		virtual void initCoordinates();
		virtual void initIndices();
		virtual void initPoints();
};


#endif


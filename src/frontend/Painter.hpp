/*
 * Painter.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __PAINTER_HPP__
#define __PAINTER_HPP__
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Applicable.hpp"          // Cast to see if item should be applied
#include "Drawable.hpp"            // Cast to see if item should be drawn
#include "Manipulator.hpp"         // Draw for selected items
#include "Matrix.hpp"              // Rotating the camera
#include "Node.hpp"                // Traversing the scene graph
#include "Outline.hpp"             // Outline selected items
#include "Selectable.hpp"          // Cast to see if item could be in selection
#include "Scene.hpp"               // Moving camera and accessing root node
using std::vector;



/**
 * Paints all the items to the screen or pick buffer.
 * 
 * @ingroup frontend
 * @warning Does not flush to the buffer.
 */
class Painter {
	
	
	public :
		
		static void paint(Scene &scene,
		                  vector<Manipulator*> &manipulators,
		                  GLenum renderMode=GL_RENDER);
	
	private :
		
		static Outline outline;
		
		static void paintNode(Node *node,
		                      vector<Manipulator*> &manipulators,
		                      GLenum renderMode);
		static void paintChildren(Node *node,
		                          vector<Manipulator*> &manipulators,
		                          GLenum renderMode);
};


#endif

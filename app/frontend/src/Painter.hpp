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
// #include "Applicable.hpp"
// #include "Drawable.hpp"
#include "Item.hpp"                // Cast to see if node is (Drawable)
#include "Manipulator.hpp"         // Draw for selected items
#include "Matrix.hpp"              // Rotating the camera
#include "Node.hpp"                // Traversing the scene graph
#include "Outline.hpp"             // Outline selected items
#include "Scene.hpp"               // Moving camera and accessing root node
#include "Translation.hpp"         // Reposition other nodes (Applicable)
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

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
#include "Applicable.hpp"          // Apply modifications to scene
#include "Drawable.hpp"            // Drawing items in scene
#include "Manipulator.hpp"         // Drawing manipulators for selection
#include "Matrix.hpp"              // Rotating camera
#include "Node.hpp"                // Traversing the scene graph
#include "Outline.hpp"             // Outline selected items
#include "Selectable.hpp"          // Drawing manipulators for selection
#include "Transformation.hpp"      // Drawing manipulators for selection
#include "Scene.hpp"               // Rotating camera and accessing root node
using namespace std;



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
		
		static void paintChildren(Node *node,
		                          GLenum renderMode);
		static void paintChildrenUI(Node *node,
		                            GLenum renderMode,
		                            vector<Manipulator*> &manipulators);
		static void paintNode(Node *node,
		                      GLenum renderMode);
		static void paintNodeUI(Node *node,
		                        GLenum renderMode,
		                        vector<Manipulator*> &manipulators);
};


#endif

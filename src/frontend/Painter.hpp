/*
 * Painter.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PAINTER_HPP
#define PAINTER_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Applicable.hpp"          // Apply modifications to scene
#include "Cube.hpp"                // Outline selected items
#include "Drawable.hpp"            // Drawing items in scene
#include "Framebuffer.hpp"         // Disable manipulators
#include "Manipulator.hpp"         // Drawing manipulators for selection
#include "Matrix.hpp"              // Rotating camera
#include "Node.hpp"                // Traversing the scene graph
#include "Program.hpp"             // Disable GLSL for outlines
#include "Selectable.hpp"          // Drawing manipulators for selection
#include "Texture.hpp"             // Pausing and restarting texturing
#include "Transformation.hpp"      // Drawing manipulators for selection
#include "Scene.hpp"               // Rotating camera and accessing root node
#include "Vector.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief
 *     Paints all the items to the screen or pick buffer.
 * 
 * @warning Does not flush to the buffer.
 */
class Painter {
	
	public:
		
		Painter(Scene *scene,
		        GLenum mode=GL_RENDER);
		void addManipulator(Manipulator *manipulator);
		void paint();
		void setMode(GLenum mode);
	
	protected:
		
		void disableTexturing();
		void paintChildren(Node *node);
		void paintNode(Node *node);
		void paintUIElements(Selectable *selectable);
		
	private:
		
		Scene *scene;
		vector<Manipulator*> manipulators;
		GLenum mode;
};


/**
 * Stores a manipulator to paint for selected items.
 */
inline void Painter::addManipulator(Manipulator *manipulator) {
	
	manipulators.push_back(manipulator);
}


/**
 * Sets the rendering mode.
 */
inline void Painter::setMode(GLenum mode) {this->mode = mode;}


#endif

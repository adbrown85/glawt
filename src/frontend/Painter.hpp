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
#include "AdvancedFactory.hpp"     // Outline selected items
#include "BasicFactory.hpp"        // Outline selected items
#include "Applicable.hpp"          // Apply modifications to scene
#include "Drawable.hpp"            // Drawing items in scene
#include "Manipulator.hpp"         // Drawing manipulators for selection
#include "Matrix.hpp"              // Rotating camera
#include "Node.hpp"                // Traversing the scene graph
#include "Program.hpp"             // Disable GLSL for outlines
#include "Texture.hpp"             // Pausing and restarting texturing
#include "Transformation.hpp"      // Drawing manipulators for selection
#include "Traverser.hpp"
#include "Scene.hpp"               // Rotating camera and accessing root node
#include "Vector.hpp"
#include "Window.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief Paints all the items to the screen or pick buffer.
 * 
 * @warning Does not flush to the buffer.
 */
class Painter : public Traverser {
public:
	Painter(Scene *scene, GLenum mode=GL_RENDER);
	void addManipulator(Manipulator *manipulator);
	virtual void start();
	void setMode(GLenum mode);
protected:
	virtual void onApplicable(Applicable *node);
	virtual void onDrawable(Drawable *node);
private:
	static bool tried;
	GLenum mode;
	static Scene *outline;
	vector<Manipulator*> manipulators;
};

/** Stores a manipulator to paint for selected items. */
inline void Painter::addManipulator(Manipulator *m) {manipulators.push_back(m);}

/** Sets the rendering mode. */
inline void Painter::setMode(GLenum mode) {this->mode = mode;}


#endif

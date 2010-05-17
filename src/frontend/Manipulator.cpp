/*
 * Manipulator.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Manipulator.hpp"


/** Creates a manipulator that cannot send commands yet. */
Manipulator::Manipulator() {
	
	this->interpreter = NULL;
}


/** Calculates how a pixel compares to a global unit.
 * 
 * @param shapeID ID of the shape to use for the depth component.
 */
float Manipulator::findPixelFactor(GLuint shapeID) {
	
	float pixelsPerUnit, depth, screenX;
	Node *node;
	Vector clip, proj;
	
	// Get depth of the shape
	node = dynamic_cast<Node*>(Identifiable::findByID(shapeID));
	depth = node->getDepth() + Window::getPosition().z;
	
	// Transform unit vector at that depth to clip space
	proj = Transform::getProjectionMatrix() * Vector(1,0,depth,1);
	clip = proj / proj.w;
	
	// Calculate how many pixels that represents on screen
	screenX = ((clip.x + 1.0) * 0.5) * Window::getWidth();
	pixelsPerUnit = screenX - (Window::getWidth() * 0.5);
	return 1 / pixelsPerUnit;
}


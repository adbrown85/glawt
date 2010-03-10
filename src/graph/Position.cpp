/*
 * Position.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Position.hpp"


/**
 * Creates a position for a light.
 */
Position::Position(const Tag &tag) {
	
	className = "Position";
	x = 0.0;
	y = 0.0;
	z = 0.0;
	tag.get("x", x, false);
	tag.get("y", y, false);
	tag.get("z", z, false);
}


/**
 * Sets the position of the light above this node.
 */
void Position::associate() {
	
	float position[4] = {x, y, z, 1.0};
	Light *light;
	
	// Find the light
	light = Light::find(this);
	if (light == NULL)
		throw "[Gander,Position] Could not find light.";
	
	// Set position
	glLightfv(light->getHandle(), GL_POSITION, position);
}


/**
 * Forms a string from the object's attributes.
 */
string Position::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " x='" << x << "'"
	       << " y='" << y << "'"
	       << " z='" << z << "'";
	return stream.str();
}


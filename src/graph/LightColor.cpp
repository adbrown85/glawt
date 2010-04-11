/*
 * LightColor.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "LightColor.hpp"


/**
 * Creates a color for a light.
 */
LightColor::LightColor(const Tag &tag) {
	
	className = "LightColor";
	r = 0.0;
	g = 0.0;
	b = 0.0;
	tag.get("r", r, false);
	tag.get("g", g, false);
	tag.get("b", b, false);
}


/**
 * Sets the color of a light above it.
 * 
 * @throws const_char* if it cannot find a light above it in the scene.
 */
void LightColor::associate() {
	
	GLfloat color[3]={r,g,b};
	Light *light;
	
	// Find light
	light = Light::find(this);
	if (light == NULL)
		throw "[LightColor] Could not find light.";
	
	// Set color
	initType();
	glLightfv(light->getHandle(), type, color);
}


/**
 * Forms a string from the object's attributes.
 */
string LightColor::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " r='" << r << "'"
	       << " g='" << g << "'"
	       << " b='" << b << "'";
	return stream.str();
}


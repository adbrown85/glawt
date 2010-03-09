/*
 * Ambient.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Ambient.hpp"


/**
 * Creates an ambient color for a light.
 */
Ambient::Ambient(const Tag &tag) : LightColor(tag) {
	
	className = "Ambient";
}


/**
 * Initializes the type of the light color.
 */
void Ambient::initType() {
	
	type = GL_AMBIENT;
}


/*
 * Diffuse.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Diffuse.hpp"


/**
 * Creates a diffuse color for a light.
 */
Diffuse::Diffuse(const Tag &tag) : LightColor(tag) {
	
	className = "Diffuse";
}


/**
 * Initializes the type of the light color.
 */
void Diffuse::initType() {
	
	type = GL_DIFFUSE;
}


/*
 * Specular.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Specular.hpp"



/**
 * Creates an ambient color for a light.
 */
Specular::Specular(const Tag &tag) : LightColor(tag) {
	
	className = "Specular";
}



/**
 * Initializes the type of the light color.
 */
void Specular::initType() {
	
	type = GL_SPECULAR;
}


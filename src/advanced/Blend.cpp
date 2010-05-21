/*
 * Blend.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Blend.hpp"


/** Enables blending. */
void Blend::apply() {
	
	glEnable(GL_BLEND);
	glDepthFunc(GL_ALWAYS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


/** Disables blending. */
void Blend::remove() {
	
	glDepthFunc(GL_LESS);
	glDisable(GL_BLEND);
}


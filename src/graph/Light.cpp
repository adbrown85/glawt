/*
 * Light.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Light.hpp"
int Light::active_lights=0;


/**
 * Creates a new light.
 */
Light::Light(const Tag &tag) {
	
	className = "Light";
	handle = GL_LIGHT0;
}


/**
 * Determines which number this light is.
 */
void Light::associate() {
	
	Node *current;
	Light *light;
	
	// Set handle
	current = this->parent;
	while (current != NULL) {
		light = dynamic_cast<Light*>(current);
		if (light != NULL) {
			handle = light->getHandle() + 1;
			break;
		}
		current = current->getParent();
	}
	
	// Verify
	if (handle > GL_LIGHT7)
		throw "[Gander,Light] Can only have eight lights.";
}


/**
 * Enables the light.
 */
void Light::apply() {
	
	glEnable(GL_LIGHTING);
	glEnable(handle);
	++active_lights;
}


/**
 * Finds the next %Light above a node.
 */
Light* Light::find(Node *node) {
	
	Node *current;
	Light *light;
	
	// Look up tree for light
	current = node->getParent();
	while (current != NULL) {
		light = dynamic_cast<Light*>(current);
		if (light != NULL)
			break;
		current = current->getParent();
	}
	return light;
}


/**
 * Temporarily disables all lighting.
 */
void Light::pause() {
	
	if (active_lights > 0)
		glDisable(GL_LIGHTING);
}


/**
 * Disables the light.
 */
void Light::remove() {
	
	glDisable(handle);
	--active_lights;
	if (active_lights == 0)
		glDisable(GL_LIGHTING);
}


/**
 * Enables all lighting after it had been temporarily disabled.
 */
void Light::restart() {
	
	if (active_lights > 0)
		glEnable(GL_LIGHTING);
}


/**
 * Forms a string from the object's attributes.
 */
string Light::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " handle='" << handle << "'";
	return stream.str();
}


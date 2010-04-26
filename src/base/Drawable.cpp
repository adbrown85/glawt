/*
 * Drawable.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Drawable.hpp"


/**
 * Initializes the item as hidden and sets the size.
 * 
 * @param size Size of the object.
 */
Drawable::Drawable(float size) {
	
	this->visible = true;
	this->size = size;
}


/**
 * Creates a new Drawable from an XML tag.
 * 
 * @param tag XML tag with "size" attribute.
 */
Drawable::Drawable(const Tag &tag) {
	
	// Initialize attributes
	this->visible = true;
	if (!tag.get("size", size, false))
		size = 1.0;
}


/**
 * Makes a drawable object the same size as another.
 * 
 * @param other Reference to another drawable object.
 */
void Drawable::copySizeOf(const Drawable &other) {
	
	size = other.size;
}


/**
 * Makes the item invisible, or more accurately marks it as not to be drawn.
 */
void Drawable::hide() {
	
	visible = false;
}


/**
 * Checks if the item is visible.
 */
bool Drawable::isVisible() const {
	
	return visible;
}


/**
 * Makes the item visible, or more accurately marks it as to be drawn.
 */
void Drawable::show() {
	
	visible = true;
}


/**
 * Switches whether the item should be drawn or not.
 */
void Drawable::toggleVisibility() {
	
	visible = !visible;
}


string Drawable::toString() const {
	
	char visibleChar;
	stringstream stream;
	
	// Format
	visibleChar = visible ? 'T' : 'F';
	
	// Make string
	stream << Identifiable::toString();
	stream << " vis='" << visibleChar << "'"
	       << " siz='" << size << "'";
	return stream.str();
}


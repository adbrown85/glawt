/*
 * Selectable.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Selectable.hpp"


/**
 * Initializes the items as deselected.
 * 
 * @param size Size of the object.
 */
Selectable::Selectable(const string &className,
                       float size) : 
                       Drawable(className, size) {
	
	selected = false;
}


/**
 * Creates a new %Selectable from an XML tag.
 * 
 * @param tag XML tag with size information.
 */
Selectable::Selectable(const string &className,
                       const Tag &tag) : 
                       Drawable(className, tag) {
	
	selected = false;
}


/**
 * Marks the item as not selected.
 * 
 * The item should not be used for operations on selections.
 */
void Selectable::deselect() {
	
	selected = false;
}


/**
 * Checks if the item is selected.
 */
bool Selectable::isSelected() const {
	
	return selected;
}


/**
 * Marks the item as selected.
 * 
 * The item should be used for operations on selections.
 */
void Selectable::select() {
	
	selected = true;
}


/**
 * Switches whether the item is selected or not.
 */
void Selectable::toggleSelected() {
	
	selected = !selected;
}


string Selectable::toString() const {
	
	char selectedChar;
	stringstream stream;
	
	// Format
	selectedChar = selected ? 'T' : 'F';
	
	// Make string
	stream << Drawable::toString();
	stream << " sel='" << selectedChar << "'";
	return stream.str();
}


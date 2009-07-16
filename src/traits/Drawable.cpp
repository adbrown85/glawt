/*
 * Drawable.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Drawable.hpp"



/**
 * Initializes the item as hidden and sets the size to 1.0.
 */
Drawable::Drawable() {
	
	visible = false;
	size = 1.0;
}



/**
 * Makes a drawable object the same size as another.
 * 
 * @param other
 *     Reference to another drawable object.
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



ostream& operator<<(ostream &stream,
                    const Drawable &item) {
	
	using namespace std;
	string visibility;
	
	// Format
	visibility = item.visible ? "T" : "F";
	
	// Print
	stream << fixed << setprecision(2);
	stream << static_cast<Identifiable>(item) << ", "
	       << "vis=" << visibility << ", "
	       << "siz=" << item.size;
	
	// Finish
	stream << resetiosflags(ios_base::floatfield) << setprecision(6);
	return stream;
}

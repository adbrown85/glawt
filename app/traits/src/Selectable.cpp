/*
 * Selectable.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Selectable.hpp"



/**
 * Initializes the items as deselected.
 */
Selectable::Selectable() {
	
	selected = false;
}



/**
 * Marks the item as not selected.  The item should not be used for 
 * operations on selections.
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
 * Marks the item as selected.  The item should be used for operations 
 * on selections.
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



ostream& operator<<(ostream &stream,
                    const Selectable &item) {
	
	string selected;
	
	// Format
	selected = item.selected ? "T" : "F";
	
	// Print
	stream << static_cast<Drawable>(item) << ", "
	       << "sel=" << selected;
	return stream;
}

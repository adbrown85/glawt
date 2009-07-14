/*
 * Selection.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Selection.hpp"



/**
 * Adds a selectable item to the selection.
 */
void Selection::add(Selectable *item) {
	
	item->select();
	items.insert(item);
}



/**
 * Returns an iterator to the beginning of the selection.
 */
Selection::iterator Selection::begin() {
	
	return items.begin();
}



/**
 * Returns an iterator to the beginning of the selection.
 */
Selection::iterator Selection::end() {
	
	return items.end();
}



/**
 * Removes a selectable item from the selection.
 */
void Selection::remove(Selectable *item) {
	
	iterator si;
	
	// Find and erase the item
	si = items.find(item);
	if (si != items.end()) {
		item->deselect();
		items.erase(si);
	}
}

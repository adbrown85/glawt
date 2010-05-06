/*
 * Selection.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Selection.hpp"


/** Adds a single item to the selection. */
void Selection::add(Drawable *item) {
	
	// Make sure selectable and visible
	if (!item->isSelectable() || !item->isVisible())
		return;
	
	// Select it
	item->setSelected(true);
	items.insert(item);
}


/** Recursively adds all the children of a node.*/
void Selection::addAll(Node *node) {
	
	Node::iterator it;
	Drawable *drawable;
	
	// Add item if drawable
	if ((drawable = dynamic_cast<Drawable*>(node)))
		add(drawable);
	
	// Add children
	for (it=node->begin(); it!=node->end(); ++it)
		addAll(*it);
}


/** Removes all the items from the selection. */
void Selection::clear() {
	
	iterator si;
	
	// Deselect and clear
	for (si=items.begin(); si!=items.end(); ++si)
		(*si)->setSelected(false);
	items.clear();
}


/** Removes a single item from the selection. */
void Selection::remove(Drawable *item) {
	
	iterator si;
	
	// Find and erase the item
	si = items.find(item);
	if (si != items.end()) {
		item->setSelected(false);
		items.erase(si);
	}
}


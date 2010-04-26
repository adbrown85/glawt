/*
 * Selection.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
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
 * Recursively adds all the children of a node.
 */
void Selection::addAll(Node *node) {
	
	Selectable *selectable;
	vector<Node*> children;
	
	// Add item if 
	selectable = dynamic_cast<Selectable*>(node);
	if (selectable != NULL)
		add(selectable);
	
	// Add children
	children = node->getChildren();
	for (size_t i=0; i<children.size(); ++i)
		addAll(children[i]);
}


/**
 * Returns an iterator to the beginning of the selection.
 */
Selection::iterator Selection::begin() {
	
	return items.begin();
}


/**
 * Removes all the items from the selection.
 */
void Selection::clear() {
	
	iterator si;
	
	// Deselect and clear
	for (si=items.begin(); si!=items.end(); ++si)
		(*si)->deselect();
	items.clear();
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


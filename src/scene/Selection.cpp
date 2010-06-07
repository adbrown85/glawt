/*
 * Selection.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Selection.hpp"


/** Adds a single item to the selection. */
void Selection::add(Node *node) {
	
	Drawable *drawable;
	
	// Cast
	drawable = dynamic_cast<Drawable*>(node);
	if (!drawable) {
		return;
	}
	
	// Make sure selectable and visible
	if (!drawable->isSelectable() || !drawable->isVisible())
		return;
	
	// Select it
	drawable->setSelected(true);
	items.insert(drawable);
	active = node;
	fireEvent();
}


/** Recursively adds all the children of a node.*/
void Selection::addAll(Node *node) {
	
	Node::iterator it;
	
	// Add node
	add(node);
	
	// Add children
	for (it=node->begin(); it!=node->end(); ++it)
		addAll(*it);
}


void Selection::addListener(NodeListener *listener) {
	
	notifier.addListener(listener, NodeEvent::MODIFY);
}


/** Removes all the items from the selection. */
void Selection::clear() {
	
	iterator si;
	
	// Deselect and clear
	for (si=items.begin(); si!=items.end(); ++si)
		(*si)->setSelected(false);
	items.clear();
}


void Selection::fireEvent() {
	
	notifier.fireEvent(NodeEvent(active, NodeEvent::MODIFY));
}


/** Removes a single item from the selection. */
void Selection::remove(Node *node) {
	
	iterator it;
	Drawable *drawable;
	
	// Cast
	drawable = dynamic_cast<Drawable*>(node);
	if (!drawable) {
		return;
	}
	
	// Find and erase the item
	it = items.find(drawable);
	if (it != items.end()) {
		drawable->setSelected(false);
		items.erase(it);
	}
}


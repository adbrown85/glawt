/*
 * Compositor.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Compositor.hpp"


/**
 * Adds the commands this delegate supports and sets up handlers.
 */
Compositor::Compositor() {
	
	// Set type
	type = "Compositor";
	
	// Add handlers
	handlersZero[Command::HIDE] = &Compositor::hide;
	handlersZero[Command::SHOW_ALL] = &Compositor::showAll;
}


/**
 * Hides the items currently selected.
 * 
 * @param scene Pointer to a collection of nodes.
 * @param cmd Specific command that was issued.
 */
void Compositor::hide(Scene *scene,
                      int cmd) {
	
	Selection selection;
	Selection::iterator it;
	
	// Hide and clear the selection
	selection = scene->getSelection();
	for (it=selection.begin(); it!=selection.end(); ++it)
		(*it)->setVisible(false);
	scene->removeAllFromSelection();
}


/**
 * Shows all the %Drawable nodes in the scene.
 * 
 * @param scene Pointer to a collection of nodes.
 * @param cmd Specific command that was issued.
 */
void Compositor::showAll(Scene *scene,
                         int cmd) {
	
	showAll(scene->getRoot());
}


/**
 * Recursively shows a node and its children.
 * 
 * @param node Pointer to a node.
 */
void Compositor::showAll(Node *node) {
	
	Drawable *drawable;
	Node::iterator it;
	
	// Show node
	drawable = dynamic_cast<Drawable*>(node);
	if (drawable != NULL)
		drawable->setVisible(true);
	
	// Show children
	for (it=node->begin(); it!=node->end(); ++it)
		showAll(*it);
}


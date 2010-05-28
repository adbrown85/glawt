/*
 * Compositor.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Compositor.hpp"


/** Hides the items currently selected. */
void Compositor::hide(int cmd) {
	
	Selection selection;
	Selection::iterator it;
	
	// Hide and clear the selection
	selection = scene->getSelection();
	for (it=selection.begin(); it!=selection.end(); ++it)
		(*it)->setVisible(false);
	scene->removeAllFromSelection();
}


/** Shows all the %Drawable nodes in the scene. */
void Compositor::showAll(int cmd) {
	
	Drawable *drawable;
	Node *node;
	Node::iterator it;
	queue<Node*> Q;
	
	Q.push(scene->getRoot());
	while (!Q.empty()) {
		node = Q.front();
		drawable = dynamic_cast<Drawable*>(node);
		if (drawable != NULL)
			drawable->setVisible(true);
		for (it=node->begin(); it!=node->end(); ++it)
			Q.push(*it);
		Q.pop();
	}
}


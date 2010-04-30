/*
 * Traverser.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Traverser.hpp"


Traverser::Traverser(Scene *scene) {
	
	this->scene = scene;
}


void Traverser::onApplicable(Node *node) {
	
	Applicable *applicable=((Applicable*)node);
	
	// Apply, do children, then remove
	applicable->apply();
	traverseChildren(node);
	applicable->remove();
}


void Traverser::onDrawable(Node *node) {
	
	Drawable *drawable=((Drawable*)node);
	Selectable *selectable;
	
	// Check if not visible
	if (!drawable->isVisible())
		return;
	
	// Draw the node and check if also selectable
	drawable->draw();
	if ((selectable = dynamic_cast<Selectable*>(drawable))) {
		onSelectable(node);
	}
	
	// Children
	traverseChildren(node);
}


void Traverser::onSelectable(Node *node) {
	
	Selectable *selectable=((Selectable*)node);
	
	// Check if not selected
	if (!selectable->isSelected()) {
		return;
	}
}


void Traverser::start() {
	
	Node *root;
	
	root = scene->getRoot();
	if (root == NULL) {
		throw "[Traverser] Scene's root is NULL.";
	}
	traverseNode(root);
}


void Traverser::traverseChildren(Node *node) {
	
	vector<Node*> children;
	vector<Node*>::iterator it;
	
	// Traverse each child
	children = node->getChildren();
	for (it=children.begin(); it!=children.end(); ++it) {
		traverseNode(*it);
	}
}


void Traverser::traverseNode(Node *node) {
	
	Applicable *applicable;
	Drawable *drawable;
	
	// Determine if node is applicable or drawable
	if ((applicable = dynamic_cast<Applicable*>(node))) {
		onApplicable(node);
	} else if ((drawable = dynamic_cast<Drawable*>(node))) {
		onDrawable(node);
	} else {
		traverseChildren(node);
	}
}


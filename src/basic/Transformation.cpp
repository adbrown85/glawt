/*
 * Transformation.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Transformation.hpp"


/** Finds all the transforms above a node. */
void Transformation::findAll(Node *node, list<Transformation*> &L) {
	
	Transformation* transform;
	
	// Find all the transforms above the node
	while (node != NULL) {
		transform = dynamic_cast<Transformation*>(node);
		if (transform != NULL) {
			L.push_front(transform);
		}
		node = node->getParent();
	}
}


/** Finds all the transforms under a node. */
void Transformation::search(Node *node, list<Transformation*> &L) {
	
	queue<Node*> Q;
	Node::iterator it;
	Transformation *transform;
	
	Q.push(node);
	while (!Q.empty()) {
		node = Q.front();
		transform = dynamic_cast<Transformation*>(node);
		if (transform != NULL)
			L.push_back(transform);
		for (it=node->begin(); it!=node->end(); ++it)
			Q.push(*it);
		Q.pop();
	}
}


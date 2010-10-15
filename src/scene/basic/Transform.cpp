/*
 * Transform.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Transform.hpp"


/** Finds all the transforms above a node. */
void Transform::findAll(Node *node, list<Transform*> &L) {
	
	Transform* transform;
	
	// Find all the transforms above the node
	while (node != NULL) {
		transform = dynamic_cast<Transform*>(node);
		if (transform != NULL) {
			L.push_front(transform);
		}
		node = node->getParent();
	}
}


/** Finds all the transforms under a node. */
void Transform::search(Node *node, list<Transform*> &L) {
	
	queue<Node*> Q;
	Node::iterator it;
	Transform *transform;
	
	Q.push(node);
	while (!Q.empty()) {
		node = Q.front();
		transform = dynamic_cast<Transform*>(node);
		if (transform != NULL)
			L.push_back(transform);
		for (it=node->begin(); it!=node->end(); ++it)
			Q.push(*it);
		Q.pop();
	}
}


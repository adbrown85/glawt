/*
 * Scout.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Scout.hpp"


/** Finds a node under @e root of @e type. */
Node* Scout::search(Node *root, const string &type) {
	
	Node *node;
	Node::iterator it;
	queue<Node*> Q;
	string typeLower;
	
	// Conver type to lowercase
	typeLower = Text::toLower(type);
	
	// Search
	Q.push(root);
	while (!Q.empty()) {
		node = Q.front();
		if (Text::toLower(node->getClassName()) == typeLower)
			return node;
		for (it=node->begin(); it!=node->end(); ++it)
			Q.push((*it));
		Q.pop();
	}
	return NULL;
}


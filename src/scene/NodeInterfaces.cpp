/*
 * NodeInterfaces.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "NodeInterfaces.hpp"


/** Gets the name from the tag. */
Nameable::Nameable(const Tag &tag) {
	
	tag.get("name", name, false, false);
}


/** @return String with the object's name if it has one. */
string Nameable::toString() const {
	
	ostringstream stream;
	
	if (hasName())
		stream << " name='" << name << "'";
	return stream.str();
}


/** Find a named node. */
Node* Nameable::search(Node *node, const string &name) {
	
	Nameable *nameable;
	Node::iterator it;
	queue<Node*> Q;
	
	Q.push(node);
	while (!Q.empty()) {
		node = Q.front();
		nameable = dynamic_cast<Nameable*>(node);
		if ((nameable != NULL) && (nameable->getName() == name))
			return node;
		for (it=node->begin(); it!=node->end(); ++it)
			Q.push(*it);
		Q.pop();
	}
	return NULL;
}


/*
 * Group.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Group.hpp"


/** Initializes attributes.
 * 
 * @throws NodeException if a name is not specified.
 */
Group::Group(const Tag &tag) : Node(tag), Nameable(tag) {
	
	if (!hasName()) {
		NodeException e(getTag());
		e << "[Group] Must have name.";
		throw e;
	}
}


/** Finds a group above the node. */
Group* Group::find(Node *node) {
	
	Group *group;
	
	while (node != NULL) {
		group = dynamic_cast<Group*>(node);
		if (group != NULL) {
			return group;
		}
		node = node->getParent();
	}
	return NULL;
}


Group* Group::find(Node *node,
                   const string &name) {
	
	Group *group;
	Node *root;
	Node::iterator it;
	
	// Look through
	root = Node::findRoot(node);
	for (it=root->begin(); it!=root->end(); ++it) {
		group = dynamic_cast<Group*>(*it);
		if (group == NULL)
			continue;
		if (group->getName() == name)
			return group;
	}
	return NULL;
}


string Group::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	stream << " name='" << getName() << "'";
	return stream.str();
}


/*
 * Group.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Group.hpp"


Group::Group(const Tag &tag) {
	
	tag.get("name", name);
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
	stream << " name='" << name << "'";
	return stream.str();
}


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
	vector<Node*> children;
	vector<Node*>::iterator it;
	
	// Look through
	root = Node::findRoot(node);
	children = root->getChildren();
	for (it=children.begin(); it!=children.end(); ++it) {
		group = dynamic_cast<Group*>(*it);
		if (group == NULL)
			continue;
		if (group->getName() == name)
			return group;
	}
	return NULL;
}


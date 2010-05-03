/*
 * Node.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Node.hpp"


/**
 * Creates a new node with no parent.
 */
Node::Node() {
	
	// Initialize
	this->depth = 0.0;
	this->parent = NULL;
}


/**
 * Adds a child to this node.
 * 
 * @param child Child node.
 */
void Node::addChild(Node *child) {
	
	// Link nodes together
	child->parent = this;
	children.push_back(child);
}


/**
 * Compares two Node pointers by depth.
 */
bool Node::compare(Node *A,
                   Node *B) {
	
	return A->depth < B->depth;
}


void Node::destroy(Node *node) {
	
	vector<Node*>::iterator it;
	
	for (it=node->children.begin(); it!=node->children.end(); ++it)
		destroy(*it);
	
	if (node != NULL)
		delete node;
}


string Node::getClassName() const {
	
	string className;
	int pos;
	
	className = typeid(*this).name();
	pos = Text::findFirstWordCharacter(className);
	return className.substr(pos);
}


ostream& operator<<(ostream &stream,
                    const Node &node) {
	
	stream << node.toString();
	return stream;
}


string Node::toString() const {
	
	ostringstream stream;
	
	// Make string
	stream << getClassName();
	return stream.str();
}


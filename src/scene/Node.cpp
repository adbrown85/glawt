/*
 * Node.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Node.hpp"


/** Creates a new node with no parent. */
Node::Node(const Tag &tag) {
	
	// Initialize
	this->depth = 0.0;
	this->parent = NULL;
	this->tag = tag;
}


/** Adds a child to this node. */
void Node::addChild(Node *child) {
	
	// Link nodes together
	child->parent = this;
	children.push_back(child);
}


/** Compares two Node pointers by depth. */
bool Node::compare(Node *A, Node *B) {
	
	return A->depth < B->depth;
}


void Node::destroy(Node *node) {
	
	vector<Node*>::iterator it;
	
	if (node->areChildrenDestroyable()) {
		for (it=node->children.begin(); it!=node->children.end(); ++it) {
			destroy(*it);
		}
	}
	
	if (node != NULL)
		delete node;
}


Node* Node::findRoot(Node *node) {
	
	Node *curr, *prev;
	
	prev = node;
	curr = node->getParent();
	while (curr != NULL) {
		prev = curr;
		curr = curr->getParent();
	}
	return prev;
}


string Node::getClassName() const {
	
	string className;
	int pos;
	
	className = typeid(*this).name();
	pos = Text::findFirstWordCharacter(className);
	return className.substr(pos);
}


ostream& operator<<(ostream &stream, const Node &node) {
	
	stream << node.toString();
	return stream;
}


string Node::toString() const {
	
	ostringstream stream;
	
	// Make string
	stream << getClassName();
	return stream.str();
}


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


/*
 * Node.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Node.hpp"



/**
 * Creates a new node with no parent.
 */
Node::Node() {
	
	// Initialize
	className = "Node";
	parent = NULL;
}



/**
 * Adds a child to this node.
 * 
 * @param child
 *     Child node.
 */
void Node::addChild(Node *child) {
	
	// Link nodes together
	child->parent = this;
	children.push_back(child);
}



/**
 * Allows nodes to traverse the graph to find other nodes.
 */
void Node::associateTree() {
	
	int numberOfChildren;
	
	// Associate self and children
	associate();
	numberOfChildren = children.size();
	for (int i=0; i<numberOfChildren; ++i)
		children[i]->associateTree();
}



/**
 * Allow nodes to finish preparing themselves after associating with others.
 */
void Node::finalizeTree() {
	
	int numberOfChildren;
	
	// Associate self and children
	finalize();
	numberOfChildren = children.size();
	for (int i=0; i<numberOfChildren; ++i)
		children[i]->finalizeTree();
}



/**
 * Prints important attributes to standard out with a small indent.
 */
void Node::print() const {
	
	// Print with indent
	print(this);
}



/**
 * Prints important attributes to standard out with a small indent.
 */
void Node::print(const Node *node) {
	
	// Print with indent
	cout << "  " << node->toString() << endl;
}



/**
 * Recursively prints important attributes to standard out.
 */
void Node::printTree() const {
	
	// Print with indent
	printTree(0);
}



/**
 * Recursively prints important attributes.
 * 
 * @param level
 *     Level of recursion used for indenting.
 */
void Node::printTree(int level) const {
	
	int count;
	string indent;
	
	// Print self
	for (int i=0; i<level; ++i)
		indent += "  ";
	cout << indent;
	print(this);
	
	// Print each child
	count = children.size();
	for (int i=0; i<count; ++i)
		children[i]->printTree(level+1);
}



string Node::toString() const {
	
	// Make string
	return className;
}

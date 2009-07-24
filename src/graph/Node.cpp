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
 * Dumps the Node's attributes to standard error.
 */
void Node::dump() const {
	
	// Add to stream
	cerr << "  "
	     << "cn=" << className << ", "
	     << "add=" << this << ", "
	     << "par=" << parent << ", "
	     << "chi=" << children.size()
	     << endl;
}



/**
 * Recursively dumps attributes to standard error.
 */
void Node::dumpTree() const {
	
	// Dump with some indent
	dumpTree(0);
}



/**
 * Recursively dumps attributes to standard error.
 * 
 * @param level
 *     Level of recursion used for indenting.
 */
void Node::dumpTree(int level) const {
	
	int numberOfChildren;
	string indent;
	
	// Dump self
	for (int i=0; i<level; ++i)
		indent += "  ";
	cerr << indent;
	dump();
	
	// Dump each child
	numberOfChildren = children.size();
	for (int i=0; i<numberOfChildren; ++i)
		children[i]->dumpTree(level+1);
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
	cout << "  " << *this << endl;
}



/**
 * Recursively prints important attributes to standard out.
 */
void Node::printTree() const {
	
	// Print with indent
	printTree(cout, 0);
}



/**
 * Recursively prints important attributes to a stream.
 * 
 * @param stream
 *     Output stream to print to.
 * @param level
 *     Level of recursion used for indenting.
 */
void Node::printTree(ostream &stream,
                     int level) const {
	
	int count;
	string indent;
	
	// Print self
	for (int i=0; i<level; ++i)
		indent += "  ";
	stream << indent;
	print();
	
	// Print each child
	count = children.size();
	for (int i=0; i<count; ++i)
		children[i]->printTree(stream, level+1);
}



ostream& operator<<(ostream &stream,
                    const Node &node) {
	
	stream << node.className;
	return stream;
}

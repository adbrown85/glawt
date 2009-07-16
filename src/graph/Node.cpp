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
 * Prints the node and its children.
 */
void Node::print() const {
	
	print(0);
}



/**
 * Recursive function for printing the node and its children.
 * 
 * @param level
 *     Level of recursion used for indenting.
 */
void Node::print(int level) const {
	
	int count;
	string indent;
	
	// Print self
	for (int i=0; i<level; ++i)
		indent += "  ";
	std::cout << indent << *this << std::endl;
	
	// Print each child
	count = children.size();
	for (int i=0; i<count; ++i)
		children[i]->print(level+1);
}



ostream& operator<<(ostream& stream,
                    const Node& node) {
	
	string parent;
	
	// Format
	parent = node.parent!=NULL ? "1" : "0";
	
	// Add to stream
	stream << "add=" << &node << ", "
	       << "par=" << node.parent << ", "
	       << "chi=" << node.children.size();
	return stream;
}

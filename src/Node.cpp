/*
 * Node.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Node.hpp"



/**
 * Adds a child to this node.
 * 
 * @param child
 *     Child node.
 */
void Node::add(Node *child) {
	
	// Link nodes together
	child->parent = this;
	children.push_back(child);
}



/**
 * Draws each of the node's children.
 */
void Node::draw() const {
	
	int count;
	
	// Draw each child
	count = children.size();
	for (int i=0; i<count; ++i)
		children[i]->draw();
}



ostream& operator<<(ostream& stream,
                    const Node& node) {
	
	// Add to stream
	stream << node.type;
	return stream;
}



/**
 * Prints the node and its children.
 */
void Node::print(int level) const {
	
	int count;
	string prefix;
	
	// Print self
	for (int i=0; i<level; ++i)
		prefix += "  ";
	std::cout << prefix << *this << std::endl;
	
	// Print each child
	count = children.size();
	for (int i=0; i<count; ++i)
		children[i]->print(level+1);
}

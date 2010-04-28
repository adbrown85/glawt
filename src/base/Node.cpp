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
	className = "Node";
	depth = 0.0;
	parent = NULL;
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
 * Compares two Node pointers by depth.
 */
bool compare(Node *A,
             Node *B) {
	
	return A->depth < B->depth;
}


/**
 * Computes the node's depth by averaging its children's depths.
 */
void Node::computeDepth(Matrix &matrix) {
	
	float avg=0.0, tot=0.0;
	int numOfChildren;
	
	// Sum depths of children
	numOfChildren = children.size();
	for (int i=0; i<numOfChildren; ++i)
		tot += children[i]->depth;
	
	// Average total
	if (numOfChildren > 0)
		avg = tot / numOfChildren;
	depth = avg;
}


void Node::destroy(Node *node) {
	
	vector<Node*>::iterator it;
	
	for (it=node->children.begin(); it!=node->children.end(); ++it)
		destroy(*it);
	
	if (node != NULL)
		delete node;
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


void Node::prepare() {
	
	associateTree();
	finalizeTree();
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
 * @param level Level of recursion used for indenting.
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


void Node::sortByDepth(Matrix &matrix) {
	
	int numOfChildren;
	
	// Start
	sortByDepthBeg(matrix);
	
	// Sort children
	numOfChildren = children.size();
	for (int i=0; i<numOfChildren; ++i)
		children[i]->sortByDepth(matrix);
	if (numOfChildren > 1)
		sort(children.begin(), children.end(), compare);
	
	// Compute own depth
	computeDepth(matrix);
	
	// Finish
	sortByDepthEnd(matrix);
}


string Node::toString() const {
	
	ostringstream stream;
	
	// Make string
	stream << className;
	return stream.str();
}


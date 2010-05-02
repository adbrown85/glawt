/*
 * Node.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef NODE_HPP
#define NODE_HPP
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>
#include "Matrix.hpp"
#include "Text.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief Basic element of the scene graph.
 */
class Node {
public:
	Node();
	virtual ~Node() {};
	void addChild(Node *child);
	virtual void associateTree();
	static bool compare(Node *A, Node *B);
	static void destroy(Node *node);
	virtual void finalizeTree();
	virtual vector<Node*> getChildren() const;
	int getChildrenSize() const;
	string getClassName() const;
	float getDepth() const;
	Node* getParent() const;
	virtual void prepare();
	static void print(const Node *node);
	virtual void print() const;
	virtual void printTree() const;
	void setChildren(const vector<Node*> children);
	void setDepth(float depth);
	void setParent(Node *parent);
	//virtual void sortByDepth(Matrix &matrix);
	virtual string toString() const;
protected:
	float depth;
	Node *parent;
	vector<Node*> children;
	virtual void associate() {}
	//virtual void computeDepth(Matrix &matrix);
	virtual void finalize() {}
	virtual void printTree(int level) const;
	//virtual void sortByDepthBeg(Matrix &matrix) {}
	//virtual void sortByDepthEnd(Matrix &matrix) {}
};


inline vector<Node*> Node::getChildren() const {return children;}
inline int Node::getChildrenSize() const {return children.size();}
inline float Node::getDepth() const {return depth;}
inline Node* Node::getParent() const {return parent;}
inline void Node::setChildren(const vector<Node*> children) {
	this->children = children;
}
inline void Node::setDepth(float depth) {
	this->depth = depth;
}
inline void Node::setParent(Node *parent) {
	this->parent = parent;
}


#endif

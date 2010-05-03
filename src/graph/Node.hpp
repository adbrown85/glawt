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
	virtual void associate() {}
	static bool compare(Node *A, Node *B);
	static void destroy(Node *node);
	virtual void finalize() {}
	virtual vector<Node*> getChildren() const;
	int getChildrenSize() const;
	string getClassName() const;
	float getDepth() const;
	Node* getParent() const;
	friend ostream& operator<<(ostream &stream, const Node *node);
	void setChildren(const vector<Node*> children);
	void setDepth(float depth);
	void setParent(Node *parent);
	virtual string toString() const;
protected:
	float depth;
	Node *parent;
	vector<Node*> children;
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

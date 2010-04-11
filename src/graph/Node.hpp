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
using namespace std;


/**
 * @ingroup graph
 * @brief
 *     Basic element of the scene graph.
 */
class Node {
	
	public :
		
		Node();
		void addChild(Node *child);
		virtual void associateTree();
		virtual void finalizeTree();
		virtual void print() const;
		virtual void printTree() const;
		virtual void sortByDepth(Matrix &matrix);
		virtual string toString() const;
		
		static void print(const Node *node);
		friend bool compare(Node *A, Node *B);
		
		vector<Node*> getChildren() const {return children;}
		float getDepth() const {return depth;}
		string getClassName() const {return className;}
		Node* getParent() const {return parent;}
	
	protected :
		
		float depth;
		Node *parent;
		string className;
		vector<Node*> children;
		
		virtual void associate() {}
		virtual void computeDepth(Matrix &matrix);
		virtual void finalize() {}
		virtual void printTree(int level) const;
		virtual void sortByDepthBeg(Matrix &matrix) {}
		virtual void sortByDepthEnd(Matrix &matrix) {}
};


#endif

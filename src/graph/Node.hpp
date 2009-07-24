/*
 * Node.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef NODE_HPP
#define NODE_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
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
		virtual void dump() const;
		virtual void dumpTree() const;
		virtual void dumpTree(int level) const;
		virtual void finalizeTree();
		virtual void print() const;
		virtual void printTree() const;
		virtual void printTree(ostream &stream,
		                       int level) const;
		
		vector<Node*> getChildren() const {return children;}
		Node* getParent() const {return parent;}
		friend ostream& operator<<(ostream &stream,
		                           const Node &node);
	
	
	protected :
		
		Node *parent;
		string className;
		vector<Node*> children;
		
		virtual void associate() {}
		virtual void finalize() {}
};


#endif

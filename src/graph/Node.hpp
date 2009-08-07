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
		virtual void finalizeTree();
		virtual void print() const;
		virtual void printTree() const;
		virtual void printTree(int level) const;
		virtual string toString() const;
		
		static void print(const Node *node);
		
		vector<Node*> getChildren() const {return children;}
		string getClassName() const {return className;}
		Node* getParent() const {return parent;}
	
	
	protected :
		
		Node *parent;
		string className;
		vector<Node*> children;
		
		virtual void associate() {}
		virtual void finalize() {}
};


#endif

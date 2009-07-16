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
using std::ostream;
using std::string;
using std::vector;



/**
 * @ingroup graph
 * @brief
 *     Basic element of the scene graph.
 */
class Node {
	
	
	public :
		
		Node *parent;
		vector<Node*> children;
		
		Node();
		void addChild(Node *child);
		void print() const;
		
		friend ostream& operator<<(ostream& stream,
		                           const Node& node);
	
	
	protected :
		
		void print(int level) const;
};


#endif

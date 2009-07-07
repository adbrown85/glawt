/*
 * Node.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef _NODE_HPP_
#define _NODE_HPP_
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using std::ostream;
using std::string;
using std::vector;



/**
 * @brief
 *     Basic element of the scene graph.
 * @ingroup graph
 */
class Node {
	
	
	public :
		
		Node() {type = "Node";}
		friend ostream& operator<<(ostream& stream, const Node& node);
		
		void add(Node *child);
		virtual void draw() const;
		void print(int level) const;
		
		Node *parent;
		string type;
		vector<Node*> children;
};


#endif

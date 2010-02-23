/*
 * OctreeNode.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef OCTREENODE_HPP
#define OCTREENODE_HPP
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <GL/glut.h>
using namespace std;



/**
 * @ingroup graph
 * @brief
 *     Node in an octree.
 */
class OctreeNode {
	
	
	public:
		
		OctreeNode();
		
		OctreeNode* getChild(int index) {return children[index];}
		bool isEmpty();
		void setChild(int index,
		              OctreeNode *childNode) {children[index] = childNode;}
		void setEmpty(bool empty);
		string toString();
	
	
	protected:
		
		bool empty;
		OctreeNode *children[8];
};


#endif

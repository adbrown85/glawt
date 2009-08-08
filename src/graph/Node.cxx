/*
 * Node.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <iostream>
#include "Node.hpp"
#define NUMBER_OF_ITEMS 4
using namespace std;



/**
 * Unit test for Node.
 */
int main() {
	
	Node nodes[NUMBER_OF_ITEMS], root;
	Matrix rotMatrix;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Node" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Build tree
	cout << "Building tree..." << endl;
	root.addChild(&nodes[0]);
	for (int i=0; i<NUMBER_OF_ITEMS-1; ++i)
		nodes[i].addChild(&nodes[i+1]);
	
	// Sort by depth
	cout << "Sorting by depth..." << endl;
	root.sortByDepth(rotMatrix);
	
	// Print tree
	cout << "Printing tree:" << endl;
	root.printTree();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Node" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

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
	
	Node items[NUMBER_OF_ITEMS];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Node" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Dump
	cout << "Dumping each node: " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i)
		items[i].dump();
	
	// Build tree
	cout << "Building tree..." << endl;
	for (int i=0; i<NUMBER_OF_ITEMS-1; ++i)
		items[i].addChild(&items[i+1]);
	
	// Dump and print tree
	cout << "Dumping tree:" << endl;
	items[0].dumpTree();
	cout << "Printing tree:" << endl;
	items[0].printTree();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Node" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

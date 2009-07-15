/*
 * Node.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <iostream>
#include "Node.hpp"
#define NUMBER_OF_ITEMS 4



/**
 * Unit test for Node.
 */
int main() {
	
	using namespace std;
	Node items[NUMBER_OF_ITEMS];
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Node" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Print
	cout << "Nodes: " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i)
		cout << "  " << items[i] << endl;
	
	// Children
	cout << "Adding children..." << endl;
	for (int i=0; i<NUMBER_OF_ITEMS-1; ++i)
		items[i].addChild(&items[i+1]);
	cout << "Nodes: " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i)
		cout << "  " << items[i] << endl;
	
	// Print root node
	cout << "Root node:" << endl;
	items[0].print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Node" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

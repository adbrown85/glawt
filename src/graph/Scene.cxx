/*
 * Scene.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <iostream>
#include "Scene.hpp"
#include "Node.hpp"
#define NUMBER_OF_NODES 4
using namespace std;


/**
 * Unit test for Scene.
 */
int main() {
	
	Node nodes[NUMBER_OF_NODES];
	Scene scene;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Scene" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Print
	cout << "Nodes: " << endl;
	for (int i=0; i<NUMBER_OF_NODES; ++i)
		cout << "  " << nodes[i] << endl;
	
	// Children
	cout << "Adding nodes to scene..." << endl;
	for (int i=0; i<NUMBER_OF_NODES; ++i)
		scene.add(&nodes[i]);
	
	// Print
	cout << "Scene:" << endl;
	scene.print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Scene" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

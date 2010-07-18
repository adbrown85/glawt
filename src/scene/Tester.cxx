/*
 * Tester.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Tester.hpp"


Node* createNode(const Tag &tag) {
	
	return new Node(tag);
}


int main(int argc,
         char *argv[]) {
	
	Tester tester;
	
	// Initialize
	Toolkit kit(argc, argv);
	
	// Install tags
	Factory::install("program", &createNode);
	Factory::install("shader", &createNode);
	Factory::install("translate", &createNode);
	Factory::install("cube", &createNode);
	
	// Start
	tester.open("Tester.xml");
	tester.start();
	
	// Finish
	return 0;
}


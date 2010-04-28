/*
 * Tester.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Tester.hpp"


Node* createNode(const Tag &tag) {
	
	Node *node = new Node();
	
	node->setClassName(tag.name);
	return node;
}


int main(int argc,
         char *argv[]) {
	
	try {
		
		// Install tags
		Factory::install("program", &createNode);
		Factory::install("shader", &createNode);
		Factory::install("translate", &createNode);
		Factory::install("cube", &createNode);
		
		// Start factory
		Tester::init(argc, argv);
		Tester::open("Tester.xml");
		Tester::start();
	}
	catch (const char *e) {
		cerr << e << endl;
	}
	
	// Finish
	return 0;
}


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
	
	// Install tags
	Factory::install("program", &createNode);
	Factory::install("shader", &createNode);
	Factory::install("translate", &createNode);
	Factory::install("cube", &createNode);
	
	// Start
	Gtk::Main kit(argc, argv);
	Tester::init(argc, argv);
	Tester::open("Tester.xml");
	Tester::start();
	
	// Finish
	return 0;
}


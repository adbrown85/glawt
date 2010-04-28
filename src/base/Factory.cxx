/*
 * Factory.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Factory.hpp"


Node* createShape(const Tag &tag) {
	
	cout << "createShape()" << endl;
	return new Node();
}


Node* createTransform(const Tag &tag) {
	
	cout << "createTransform()" << endl;
	return new Node();
}


int main(int argc,
         char *argv[]) {
	
	Node *node;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Factory" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	Factory::install("shape", &createShape);
	Factory::install("transform", &createTransform);
	node = Factory::create(Tag("shape"));
	node = Factory::create(Tag("transform"));
	
	// End
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Factory" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}


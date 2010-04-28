/*
 * BasicFactory.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <cassert>
#include "BasicFactory.hpp"
#include "Parser.hpp"
#include "Text.hpp"


void testCreate(const string &text) {
	
	Node *node;
	Tag tag;
	
	tag = Parser::parseTag(text);
	node = Factory::create(tag);
	node->print();
}


int main(int argc,
         char *argv[]) {
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "BasicFactory" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	try {
		BasicFactory::install();
		testCreate("cube");
		testCreate("program");
		testCreate("scale");
		testCreate("shader file='../../glsl/basic.frag'");
		testCreate("square");
		testCreate("texture name='crate' file='../../textures/crate.jpg'");
		testCreate("texture file='../../textures/chunk.vlb'");
		testCreate("translate");
		testCreate("uniform type='int' name='bar'");
	} catch (const char *e) {
		cerr << e << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "BasicFactory" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}


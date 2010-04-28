/*
 * AdvancedFactory.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <cassert>
#include "AdvancedFactory.hpp"
#include "Parser.hpp"
#include "Text.hpp"


void testCreate(const string &text) {
	
	Node *node;
	Tag tag;
	
	tag = Parser::create(text);
	node = Factory::create(tag);
	node->print();
	assert(tag.name == Text::toLower(node->getClassName()));
}


int main(int argc,
         char *argv[]) {
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "AdvancedFactory" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	try {
		AdvancedFactory::install();
		testCreate("cull faces='front'");
		testCreate("framebuffer");
		testCreate("fullscreen");
		testCreate("octree name='octree' link='volume'");
		testCreate("target link='buffer'");
		testCreate("wireframe");
	} catch (const char *e) {
		cerr << e << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "AdvancedFactory" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}


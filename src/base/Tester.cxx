/*
 * Tester.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Tester.hpp"



class FakeFactory : public Factory {
	public:
		FakeFactory();
		Node* create(const Tag &tag) const;
};


FakeFactory::FakeFactory() {
	
	tags.insert("program");
	tags.insert("shader");
	tags.insert("translate");
	tags.insert("cube");
}


Node* FakeFactory::create(const Tag &tag) const {
	
	Node *node = new Node();
	
	node->setClassName(tag.name);
	return node;
}


int main(int argc,
         char *argv[]) {
	
	// Start
	try {
		Tester::init(argc, argv);
		Tester::install(new FakeFactory());
		Tester::open("Tester.xml");
		Tester::start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	
	// Finish
	return 0;
}


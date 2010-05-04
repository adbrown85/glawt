/*
 * NodeException.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "NodeException.hpp"


class NodeExceptionTest {
public:
	void setUp();
	void testThrow();
private:
	Tag tag;
};


void NodeExceptionTest::setUp() {
	
	tag.setFilename("NodeExceptionTest.xml");
	tag.setLine(27);
}


void NodeExceptionTest::testThrow() {
	
	NodeException e(tag);
	e << "This is a NodeException!";
	throw e;
}


int main(int argc,
         char *argv[]) {
	
	NodeExceptionTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "NodeException" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	try {
		test.setUp();
		test.testThrow();
	} catch (Exception &e) {
		cerr << e << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "NodeException" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}


/*
 * Exception.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Exception.hpp"


/* Test for exception. */
class ExceptionTest {
public:
	void testThrowCatch();
};

/* Throw and catch the exception. */
void ExceptionTest::testThrowCatch() {
	
	bool caught;
	int line=45;
	
	caught = false;
	try {
		Exception e;
		e << "[GLawt] This is an exception from " << line << ".";
		throw e;
	} catch (Exception &e) {
		cout << e << endl;
		caught = true;
	}
	
	if (!caught) {
		cerr << "Exception was not caught!" << endl;
		exit(1);
	}
}

/* Run the test. */
int main(int argc, char *argv[]) {
	
	ExceptionTest test;
	
	test.testThrowCatch();
}


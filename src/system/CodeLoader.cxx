/*
 * CodeLoader.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "CodeLoader.hpp"


class CodeLoaderTest {
public:
	void setUp();
	void testLines();
private:
	CodeLoader loader;
};


void CodeLoaderTest::setUp() {
	
	loader.parse("Preprocessor.glsl");
}


void CodeLoaderTest::testLines() {
	
	Code code;
	Code::iterator it;
	
	code = loader.getCode();
	for (it=code.begin(); it!=code.end(); ++it)
		cout << it->filename << " " << it->number << " " << it->text;
}


int main(int argc, char *argv[]) {
	
	CodeLoaderTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "CodeLoader" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	try {
		test.setUp();
		test.testLines();
	} catch (Exception &e) {
		cerr << e << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "CodeLoader" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}


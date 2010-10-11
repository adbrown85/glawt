/*
 * Preprocessor.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Preprocessor.hpp"


class PreprocessorTest {
public:
	void setUp();
	void testLines();
private:
	Preprocessor pp;
};


void PreprocessorTest::setUp() {
	
	pp.parse("Preprocessor.glsl");
}


void PreprocessorTest::testLines() {
	
	Code code;
	Code::iterator it;
	
	code = pp.getCode();
	for (it=code.begin(); it!=code.end(); ++it)
		cout << it->filename << " " << it->number << " " << it->text;
}


int main(int argc, char *argv[]) {
	
	PreprocessorTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Preprocessor" << endl;
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
	cout << "Preprocessor" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}


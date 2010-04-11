/*
 * Tag.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Tag.hpp"


int main() {
	
	Tag tag;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Tag" << endl;
	cout << "****************************************" << endl;
	
	// Test
	cout << "\nTesting..." << endl;
	tag.setName("Foo");
	tag.add("fOO", "bAr");
	tag.add("fIle", "/foo/Bar");
	cout << tag << endl;
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Tag" << endl;
	cout << "****************************************" << endl;
	return 0;
}


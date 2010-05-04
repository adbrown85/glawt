/*
 * Tag.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <cassert>
#include "Tag.hpp"


class TagTest {
public:
	void testCreate();
	void testGetArray();
private:
	Tag tag;
};


void TagTest::testCreate() {
	
	cout << "Creating..." << endl;
	tag.setName("Foo");
	tag["fOO"] = "bAr";
	tag["fIle"] = "/foo/Bar";
	cout << "  " << tag << endl;
}


void TagTest::testGetArray() {
	
	float value[4];
	
	cout << "\nGetting array..." << endl;
	tag["value"] = "0.4 2.1 4.5 -5.9";
	tag.get("value", value);
	for (int i=0; i<4; ++i)
		cout << "  value[" << i << "] is " << value[i] << endl;
	assert(value[0] == 0.4f);
	assert(value[1] == 2.1f);
	assert(value[2] == 4.5f);
	assert(value[3] == -5.9f);
}


int main() {
	
	TagTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Tag" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	test.testCreate();
	test.testGetArray();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Tag" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}


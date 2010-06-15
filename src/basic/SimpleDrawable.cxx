/*
 * SimpleDrawable.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <iostream>
#include "SimpleDrawable.hpp"
#define NUMBER_OF_ITEMS 4
using namespace std;


class FakeDrawable : public SimpleDrawable {
public: 
	FakeDrawable(const Tag &tag) : SimpleDrawable(tag) {}
	void draw() const {}
};


class SimpleDrawableTest {
public:
	void setUp();
	void testSetSelected();
	void testSetVisible();
	void testToggleSelected();
	void testToggleVisible();
private:
	FakeDrawable *items[NUMBER_OF_ITEMS];
};


void SimpleDrawableTest::setUp() {
	
	Tag tag;
	
	cout << "Setting up..." << endl;
	tag["size"] = "1.0";
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		items[i] = new FakeDrawable(tag);
		cout << "  " << *items[i] << endl;
	}
}


void SimpleDrawableTest::testSetSelected() {
	
	cout << "\nSetting selected... " << endl;
	items[0]->setSelected(false);
	cout << "  " << *items[0] << endl;
	cout << "  ---------------------" << endl;
	items[0]->setSelected(true);
	cout << "  " << *items[0] << endl;
}


void SimpleDrawableTest::testSetVisible() {
	
	cout << "\nSetting visible..." << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		items[i]->setVisible(true);
		cout << "  " << *items[i] << endl;
	}
	cout << "  ---------------------" << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		items[i]->setVisible(false);
		cout << "  " << *items[i] << endl;
	}
}


void SimpleDrawableTest::testToggleSelected() {
	
	cout << "\nToggling selected... " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		items[0]->toggleSelected();
		cout << "  " << *items[0] << endl;
	}
}


void SimpleDrawableTest::testToggleVisible() {
	
	cout << "\nToggling visible..." << endl;
	for (int j=0; j<3; ++j) {
		if (j != 0)
			cout << "  ---------------------" << endl;
		for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
			items[i]->toggleVisible();
			cout << "  " << *items[i] << endl;
		}
	}
}



int main() {
	
	SimpleDrawableTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "SimpleDrawable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	test.setUp();
	test.testSetVisible();
	test.testToggleVisible();
	test.testSetSelected();
	test.testToggleSelected();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "SimpleDrawable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}


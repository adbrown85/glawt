/*
 * Drawable.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <iostream>
#include "Drawable.hpp"
#define NUMBER_OF_ITEMS 4
using namespace std;


class FakeDrawable : public Drawable {
public: 
	FakeDrawable(const Tag &tag) : Drawable(tag) {}
	void draw() const {}
};


class DrawableTest {
public:
	void before();
	void testSetVisible();
	void testSetSize();
	void testToggleVisible();
private:
	FakeDrawable *items[NUMBER_OF_ITEMS];
};


void DrawableTest::before() {
	
	Tag tag;
	
	cout << "Constructing..." << endl;
	tag["size"] = "1.0";
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		items[i] = new FakeDrawable(tag);
		cout << "  " << *items[i] << endl;
	}
}


void DrawableTest::testSetVisible() {
	
	// Show
	cout << "\nShowing..." << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		items[i]->setVisible(true);
		cout << "  " << *items[i] << endl;
	}
	
	// Hide
	cout << "Hiding..." << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		items[i]->setVisible(false);
		cout << "  " << *items[i] << endl;
	}
}


void DrawableTest::testSetSize() {
	
	// Sizes
	cout << "\nSetting sizes... " << endl;
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		items[i]->setSize(i+1);
		cout << "  " << *items[i] << endl;
	}
}


void DrawableTest::testToggleVisible() {
	
	cout << "Toggling..." << endl;
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
	
	DrawableTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Drawable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	test.before();
	test.testSetSize();
	test.testSetVisible();
	test.testToggleVisible();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Drawable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}


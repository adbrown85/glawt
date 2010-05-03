/*
 * Selectable.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <iostream>
#include "Selectable.hpp"
using namespace std;


class FakeSelectable : public Selectable {
public:
	FakeSelectable(const Tag &tag) : Selectable(tag) {}
	void draw() const {}
};


class SelectableTest {
public:
	void before();
	void testDeselect();
	void testSelect();
	void testToggle();
	void after();
private:
	FakeSelectable *node;
};


void SelectableTest::before() {
	
	Tag tag;
	
	tag["selected"] = "false";
	node = new FakeSelectable(tag);
}


void SelectableTest::testDeselect() {
	
	cout << "Deselecting... " << endl;
	node->deselect();
	cout << "  " << node << endl;
}


void SelectableTest::testSelect() {
	
	cout << "Selecting... " << endl;
	node->select();
	cout << "  " << node << endl;
}


void SelectableTest::testToggle() {
	
	// Toggle
	cout << "Toggling... " << endl;
	for (int i=0; i<5; ++i) {
		node->toggleSelected();
		cout << "  " << node << endl;
	}
}


void SelectableTest::after() {
	
	delete node;
}



int main() {
	
	SelectableTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Selectable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Initialize
	test.before();
	test.testSelect();
	test.testDeselect();
	test.testToggle();
	test.after();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Selectable" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}


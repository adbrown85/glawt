/*
 * Selection.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <iostream>
#include "Selection.hpp"
#include "SimpleDrawable.hpp"
#define NUMBER_OF_NODES 4


class FakeDrawable : public SimpleDrawable {
public:
	FakeDrawable(const Tag &tag) : SimpleDrawable(tag) {}
	void draw() const {}
};


class SelectionTest {
public:
	void setUp();
	void tearDown();
	void testAdd();
	void testIterator();
	void testRemove();
private:
	Selection selection;
	FakeDrawable *nodes[NUMBER_OF_NODES];
};


void SelectionTest::setUp() {
	
	Tag tag;
	
	// Create nodes
	cout << "Setting up..." << endl;
	tag["selected"] = "false";
	for (int i=0; i<NUMBER_OF_NODES; ++i) {
		nodes[i] = new FakeDrawable(tag);
		cout << "  " << nodes[i]->getID() << ": "
		             << nodes[i]->isSelected() << endl;
	}
}


void SelectionTest::tearDown() {
	
	// Delete nodes
	cout << "\nTearing down..." << endl;
	for (int i=0; i<NUMBER_OF_NODES; ++i) {
		delete nodes[i];
	}
}


void SelectionTest::testAdd() {
	
	// Add to selection
	cout << "\nAdding to selection..." << endl;
	for (int i=0; i<NUMBER_OF_NODES; ++i)
		selection.add(nodes[i]);
}


void SelectionTest::testIterator() {
	
	Selection::iterator si;
	
	// Print selection
	cout << "\nTesting iterator..." << endl;
	for (si=selection.begin(); si!=selection.end(); ++si)
		cout << "  " << (*si)->getID() << ": " << (*si)->isSelected() << endl;
}


void SelectionTest::testRemove() {
	
	int id=3;
	Drawable *node;
	
	// Remove a node
	cout << "\nRemoving node " << id << "..." << endl;
	node = nodes[id-1];
	selection.remove(node);
	cout << "  " << node->getID() << ": " << node->isSelected() << endl;
}


/** Run unit test for Selection. */
int main() {
	
	SelectionTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Selection" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	test.setUp();
	test.testAdd();
	test.testRemove();
	test.testIterator();
	test.tearDown();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Selection" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}


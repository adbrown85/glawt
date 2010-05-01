/*
 * Selection.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <iostream>
#include "Selection.hpp"
#define NUMBER_OF_NODES 4


class FakeSelectable : public Selectable {
public:
	FakeSelectable(const Tag &tag) : Selectable(tag) {}
	void draw() const {}
};


class SelectionTest {
public:
	void before();
	void testAdd();
	void testIterator();
	void testRemove();
	void after();
private:
	Selection selection;
	FakeSelectable *nodes[NUMBER_OF_NODES];
};


void SelectionTest::before() {
	
	Tag tag;
	
	// Create nodes
	cout << "Creating nodes..." << endl;
	tag["selected"] = "false";
	for (int i=0; i<NUMBER_OF_NODES; ++i) {
		nodes[i] = new FakeSelectable(tag);
		cout << "  " << nodes[i]->getID() << ": "
		             << nodes[i]->isSelected() << endl;
	}
}


void SelectionTest::testAdd() {
	
	// Add to selection
	cout << "Adding to selection..." << endl;
	for (int i=0; i<NUMBER_OF_NODES; ++i)
		selection.add(nodes[i]);
}


void SelectionTest::testIterator() {
	
	Selection::iterator si;
	
	// Print selection
	cout << "Selection:" << endl;
	for (si=selection.begin(); si!=selection.end(); ++si)
		cout << "  " << (*si)->getID() << ": " << (*si)->isSelected() << endl;
}


void SelectionTest::testRemove() {
	
	int id=3;
	Selectable *node;
	
	// Remove a node
	cout << "Removing node " << id << "..." << endl;
	node = nodes[id-1];
	selection.remove(node);
	cout << "  " << node->getID() << ": " << node->isSelected() << endl;
}


void SelectionTest::after() {
	
	// Delete nodes
	cout << "Deleting nodes..." << endl;
	for (int i=0; i<NUMBER_OF_NODES; ++i) {
		delete nodes[i];
	}
}


/**
 * Unit test for Selection.
 */
int main() {
	
	SelectionTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Selection" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	test.before();
	test.testAdd();
	test.testIterator();
	test.testRemove();
	test.after();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Selection" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}


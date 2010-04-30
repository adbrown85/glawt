/*
 * Selection.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <iostream>
#include "Selection.hpp"


class FakeSelectable : public Selectable {
public:
	FakeSelectable() : Selectable(1.0) {}
	void draw() const {}
};


/**
 * Unit test for Selection.
 */
int main() {
	
	using namespace std;
	int id;
	FakeSelectable *item, items[4];
	Selection selection;
	Selection::iterator si;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Selection" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Initialize
	cout << boolalpha;
	cout << "Initial items: " << endl;
	for (int i=0; i<4; ++i)
		cout << "  " << items[i].getID() << ": "
		             << items[i].isSelected() << endl;
	
	// Add to selection
	cout << "Adding to selection..." << endl;
	for (int i=0; i<4; ++i)
		selection.add(&items[i]);
	
	// Print selection
	cout << "Selection:" << endl;
	for (si=selection.begin(); si!=selection.end(); ++si)
		cout << "  " << (*si)->getID() << ": " << (*si)->isSelected() << endl;
	
	// Remove item and print again
	id = 3;
	cout << "Removing item " << id << ":" << endl;
	item = &items[id-1];
	selection.remove(item);
	cout << "  " << item->getID() << ": " << item->isSelected() << endl;
	
	// Print selection
	cout << "Selection:" << endl;
	for (si=selection.begin(); si!=selection.end(); ++si)
		cout << "  " << (*si)->getID() << ": " << (*si)->isSelected() << endl;
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Selection" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}


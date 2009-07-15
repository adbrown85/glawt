/*
 * Selection.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <iostream>
#include "Selection.hpp"



/**
 * Unit test for Selection.
 */
int main() {
	
	using namespace std;
	int id;
	Selectable *item, items[4];
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

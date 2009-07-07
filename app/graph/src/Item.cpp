/*
 * Item.cpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Item.hpp"
int Item::count=0;
map<int,Item*> Item::ids;



/**
 * Creates and initializes the item.
 */
Item::Item() {
	
	// Initialize
	selected = false;
	shown = true;
	style = GL_TEXTURE_2D;
	cat = "Item";
	type = "Item";
	id = ++count;
	ids[id] = this;
}


/**
 * Formats the item's attributes into a string.
 */
std::string Item::attributes() const {
	
	std::ostringstream stream(std::ostringstream::out);
	std::string selected, shown, style;
	
	// Format
	shown = this->shown ? "V" : "H";
	selected = this->selected ? "S" : "U";
	style = this->style==GL_TEXTURE_2D ? "2D" : "3D";
	
	// Print
	stream << id << ", "
	       << shown << ", "
	       << selected << ", "
	       << style;
	
	// Finish
	return stream.str();
}



/**
 * Copies size, position, and rotation from another Item.
 * 
 * @param item
 *     Another item.
 */
void Item::copy(const Item &item) {
	
	// Copy attributes
	this->size = item.size;
	this->position = item.position;
	this->rotation = item.rotation;
}



Item* Item::find(int id) {
	
	map<int,Item*>::iterator ii;
	
	// Find
	ii = ids.find(id);
	if (ii != ids.end())
		return ii->second;
	else
		return NULL;
}


/**
 * Prints the value of several attributes to the stream.
 */
std::ostream& operator<<(std::ostream& stream,
                         const Item& item) {
	
	// Print
	stream << item.type << "{"
	       << item.attributes() << "}";
	return stream;
}



/**
 * Simple test program.
 */
/*
#include "Box.hpp"
int main(int argc, char **argv) {
	
	using namespace std;
	const int count=3;
	Box box[count];
	ItemPtrSet selection;
	ItemPtrSet::iterator it;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Item" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Array
	box[0].setID(20);
	box[1].setID(15);
	box[2].setID(20);
	cout << "Array IDs: " << endl;
	for (int i=0; i<count; i++)
		cout << "  " << box[i] << endl;
	cout << "Array addresses: " << endl;
	for (int i=0; i<count; i++)
		cout << "  " << &box[i] << endl;
	cout << endl;
	
	// Map
	cout << "Map IDs: " << endl;
	selection.insert(&box[0]);
	selection.insert(&box[1]);
	selection.insert(&box[2]);
	for (it=selection.begin(); it!=selection.end(); it++)
		cout << "  " << (*it)->getID() << endl;
	cout << "Map addresses: " << endl;
	for (it=selection.begin(); it!=selection.end(); it++)
		cout << "  " << *it << endl;
	cout << endl;
	
	// Find
	for (int i=0; i<count; i++)
		if (selection.find(&box[i]) != selection.end())
			cout << "Box with ID equal to box[" << i << "] is there!" << endl;
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Item" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
*/

/*
 * Item.cpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Item.hpp"
int Item::count=0;



/**
 * Creates and initializes the item.
 */
Item::Item() {
	
	// Initialize
	selected = false;
	style = GL_TEXTURE_2D;
	type = "Item";
	id = ++count;
}


/**
 * Formats the item's attributes into a string.
 */
std::string Item::attributes() const {
	
	std::ostringstream stream(std::ostringstream::out);
	std::string selected, style;
	
	// Format
	selected = this->selected ? "S" : "U";
	style = this->style==GL_TEXTURE_2D ? "2D" : "3D";
	
	// Print
	stream << id << ", "
	       << selected << ", "
	       << style;
	
	// Finish
	return stream.str();
}



/**
 * Draws the item.
 */
void Item::draw() const {
	
	// Draw
	std::cout << "Item::draw()" << std::endl;
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
int main(int argc, char **argv) {
	
	using namespace std;
	Item items[5];
	
	items[0].select();
	items[0].setStyle(GL_TEXTURE_3D);
	for (int i=0; i<5; i++)
		cout << items[i] << endl;
	items[0].draw();
}
*/

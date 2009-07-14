/*
 * Shape.cpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Shape.hpp"



/**
 * Creates and initializes the shape.
 */
Shape::Shape() {
	
	// Initialize
	style = GL_TEXTURE_2D;
	type = "Shape";
}



/**
 * Formats the shape's attributes into a string.
 */
string Shape::attributes() const {
	
	ostringstream stream(ostringstream::out);
	string selected, style, visible;
	
	// Format
	visible = this->isVisible() ? "V" : "H";
	selected = this->isSelected() ? "S" : "U";
	style = this->style==GL_TEXTURE_2D ? "2D" : "3D";
	
	// Print
	stream << getID() << ", "
	       << visible << ", "
	       << selected << ", "
	       << style;
	
	// Finish
	return stream.str();
}



/**
 * Prints the value of several attributes to the stream.
 */
ostream& operator<<(ostream& stream,
                    const Shape& shape) {
	
	// Print
	stream << shape.type << "{"
	       << shape.attributes() << "}";
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
	ShapePtrSet selection;
	ShapePtrSet::iterator it;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shape" << endl;
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
	cout << "Shape" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
*/

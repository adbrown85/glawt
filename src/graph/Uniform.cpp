/*
 * Uniform.cpp
 *     Container for GLSL uniform variables.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Uniform.hpp"



/**
 * Initializes a new Uniform variable with a float value.
 * 
 * @param name
 *     Name of the uniform variable.
 * @param value
 *     Value to be stored.
 */
Uniform::Uniform(string name, GLfloat value) {
	
	// Initialize
	this->name = name;
	this->value = value;
	type = UNIFORM_FLOAT;
}



/**
 * Initializes a new Uniform variable with an integer value.
 * 
 * @param name
 *     Name of the uniform variable.
 * @param value
 *     Value to be stored.
 */
Uniform::Uniform(string name, GLint value) {
	
	// Initialize
	this->name = name;
	this->value = value;
	type = UNIFORM_INT;
}



/**
 * Initializes a new Uniform variable with a float value.
 * 
 * @param name
 *     Name of the uniform variable.
 * @param type
 *     Type of the uniform variable.  Should be "int" or "float".
 * @param value
 *     Value to be stored.
 */
Uniform::Uniform(string name, string type, GLfloat value) {
	
	// Initialize
	this->name = name;
	this->value = value;
	if (type.compare("float") == 0 || type.compare("GLfloat") == 0)
		type = UNIFORM_FLOAT;
	else if (type.compare("int") == 0 || type.compare("GLint") == 0)
		type = UNIFORM_INT;
}



/**
 * Prints the uniform's attributes to a stream.
 * 
 * @param stream
 *     Output stream.
 * @param uniform
 *     Uniform variable.
 */
ostream& operator<<(ostream& stream, const Uniform &uniform) {
	
	string type;
	
	// Format
	type = uniform.type == UNIFORM_FLOAT ? "f" : "i";
	
	// Print
	stream << "["
	       << uniform.name << ", "
	       << type << ", ";
	if (uniform.type == UNIFORM_FLOAT)
		stream << std::fixed << std::setprecision(2);
	stream << uniform.value << "]";
	return stream;
}



/**
 * Simple test program.
 */
/*
int main(int argc, char **argv) {
	
	using namespace std;
	Uniform u1("u1", 1), u2("u2", 1.0f);
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Uniform" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	cout << u1 << endl;
	cout << u2 << endl;
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Uniform" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
*/

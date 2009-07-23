/*
 * Uniform.cpp
 *     Container for GLSL uniform variables.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Uniform.hpp"



/**
 * Initializes a new uniform variable with a float value.
 * 
 * @param name
 *     Name of the uniform variable.
 * @param value
 *     Float value to be stored.
 */
Uniform::Uniform(string name,
                 GLfloat value) {
	
	// Initialize
	this->name = name;
	this->value = value;
	type = 'f';
}



/**
 * Initializes a new uniform variable with an integer value.
 * 
 * @param name
 *     Name of the uniform variable.
 * @param value
 *     Integer value to be stored.
 */
Uniform::Uniform(string name,
                 GLint value) {
	
	// Initialize
	this->name = name;
	this->value = value;
	type = 'i';
}



/**
 * Initializes a new uniform variable with a value and type.
 * 
 * @param name
 *     Name of the variable.
 * @param value
 *     Value to be stored.
 * @param type
 *     Type of the variable.  Should be 'i' for int or 'f' for float.
 */
Uniform::Uniform(string name,
                 GLfloat value,
                 char type) {
	
	// Initialize
	this->name = name;
	this->value = value;
	switch (tolower(type)) {
		case 'f':
			type = 'f';
			break;
		case 'i':
			type = 'i';
			break;
		default:
			throw "Uniform: Type not supported.";
	}
}



/**
 * Installs the variable into a shader program.
 * 
 * @param program
 *     Reference to a Program object.
 */
void Uniform::install(const Program& program) {
	
	GLint location;
	
	// Look up location
	location = glGetUniformLocation(program.getName(), 
	                                name.c_str());
	if (location == -1)
		return;
	
	// Set value
	switch (type) {
		case 'f' :
			glUniform1f(location, value);
			break;
		case 'i' :
			glUniform1i(location, static_cast<int>(value));
			break;
	}
}



ostream& operator<<(ostream& stream,
                    const Uniform &uniform) {
	
	using namespace std;
	
	// Print
	stream << uniform.name << ", "
	       << uniform.type << ", ";
	if (uniform.type == 'f')
		stream << fixed << setprecision(2);
	stream << uniform.value;
	
	// Finish
	stream << resetiosflags(ios_base::floatfield)
	       << setprecision(6);
	return stream;
}


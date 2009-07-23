/*
 * Uniform.cpp
 *     Container for GLSL uniform variables.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Uniform.hpp"



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
	this->program = NULL;
	this->name = name;
	this->value = value;
	this->type = tolower(type);
	
	// Verify
	if (this->type != 'f' && this->type != 'i')
		throw "Uniform: Type not supported.";
}



/**
 * Finds a Program node that is an ancestor of this node.
 */
void Uniform::associate() {
	
	Node *current;
	
	// Look for a Program ancestor
	current = parent;
	while (current != NULL) {
		program = dynamic_cast<Program*>(current);
		if (program != NULL)
			break;
		current = current->parent;
	}
}



/**
 * Installs the variable into the program.
 */
void Uniform::finalize() {
	
	GLint location;
	
	// Check for no program
	if (program == NULL)
		return;
	
	// Look up location
	location = glGetUniformLocation(program->getName(), name.c_str());
	if (location == -1)
		return;
	
	// Set value
	switch (tolower(type)) {
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


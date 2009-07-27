/*
 * Uniform.cpp
 *     Container for GLSL uniform variables.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Uniform.hpp"
set<string> Uniform::types;



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
Uniform::Uniform(string type,
                 string name,
                 GLfloat value) {
	
	// Initialize
	className = "Uniform";
	this->program = NULL;
	this->type = type;
	this->name = name;
	this->value = value;
	
	// Verify
	initTypes();
	if (!isSupported(this->type))
		throw "Gander,Uniform: Type not supported.";
}



/**
 * Finds a Program node that is an ancestor of this node.
 */
void Uniform::associate() {
	
	Node *current;
	Texture *texture;
	
	// Look for a Program ancestor
	current = parent;
	while (current != NULL) {
		program = dynamic_cast<Program*>(current);
		if (program != NULL)
			break;
		current = current->getParent();
	}
	
	// If a sampler
	if (type.compare("sampler2D") == 0 ||
	    type.compare("sampler3D") == 0) {
		
		// Look for a texture ancestor
		current = parent;
		while (current != NULL) {
			texture = dynamic_cast<Texture*>(current);
			if (texture != NULL &&
			    texture->getName().compare(name) == 0)
				break;
			current = current->getParent();
		}
		
		// Assign unit as value if found
		if (texture != NULL)
			value = texture->getUnit();
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
	location = glGetUniformLocation(program->getName(),
	                                name.c_str());
	if (location == -1)
		return;
	
	// Set value
	if (type.compare("float") == 0)
		glUniform1f(location, value);
	else
		glUniform1i(location, static_cast<int>(value));
}



/**
 * Initializes the supported types.
 */
void Uniform::initTypes() {
	
	// Only insert once
	if (types.size() > 0)
		return;
	
	// Add to set
	types.insert("float");
	types.insert("int");
	types.insert("sampler2D");
	types.insert("sampler3D");
}



/**
 * Determines if the type is supported.
 */
bool Uniform::isSupported(string type) {
	
	set<string>::const_iterator si;
	
	// Look for type
	si = types.find(type);
	return si != types.end();
}



void Uniform::print() const {
	
	cout << "  " << *this << endl;
}



ostream& operator<<(ostream& stream,
                    const Uniform &uniform) {
	
	using namespace std;
	
	// Print
	stream << static_cast<Node>(uniform) << " "
	       << "type='" << uniform.type << "' "
	       << "name='" << uniform.name << "' "
	       << "value='" << uniform.value << "'";
	return stream;
}


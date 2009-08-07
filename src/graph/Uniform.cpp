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
                 GLfloat value,
                 string link) {
	
	// Initialize
	className = "Uniform";
	this->program = NULL;
	this->type = type;
	this->name = name;
	this->value = value;
	this->link = link;
	if (type.compare("float") == 0)
		this->valueType = GL_FLOAT;
	else
		this->valueType = GL_INT;
	verify();
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
	
	// Get unit of linked texture if a sampler
	if (isSampler()) {
		current = parent;
		while (current != NULL) {
			texture = dynamic_cast<Texture*>(current);
			if (texture != NULL && texture->getName().compare(link) == 0)
				break;
			current = current->getParent();
		}
		if (texture == NULL)
			throw "Gander,Uniform: Could not find texture linked to.";
		value = texture->getUnit();
	}
}



/**
 * Sets the value of the variable in the program.
 */
void Uniform::apply() {
	
	// Set value
	if (valueType == GL_FLOAT)
		glUniform1f(location, value);
	else
		glUniform1i(location, static_cast<int>(value));
}



/**
 * Finds the variable's location in the program.
 */
void Uniform::finalize() {
	
	// Check for no program
	if (program == NULL)
		return;
	
	// Look up location
	location = glGetUniformLocation(program->getName(), name.c_str());
	if (location == -1)
		return;
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
 * Checks if the uniform is a sampler type.
 */
bool Uniform::isSampler() {
	
	// Compare strings
	return (type.compare("sampler2D") == 0 ||
	        type.compare("sampler3D") == 0);
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
	
	cout << "  " << toString() << endl;
}



/**
 * Resets the uniform variable in the program to 0.
 */
void Uniform::remove() {
	
	// Set value
	if (valueType == GL_FLOAT)
		glUniform1f(location, 0.0f);
	else
		glUniform1i(location, 0);
}



/**
 * Checks that the Uniform's attributes are acceptable.
 */
void Uniform::verify() {
	
	// Check if type is supported
	initTypes();
	if (!isSupported(this->type))
		throw "Gander,Uniform: Type not supported.";
	
	// Check if sampler type has link
	if (isSampler() && link.empty())
		throw "Gander,Uniform: Sampler types require link.";
}



string Uniform::toString() const {
	
	stringstream stream;
	
	// Print
	stream << Node::toString();
	stream << " type='" << type << "'"
	       << " name='" << name << "'"
	       << " value='" << value << "'"
	       << " link='" << link << "'";
	return stream.str();
}


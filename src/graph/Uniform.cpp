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
 * @param type
 *     Type of the variable.
 * @param name
 *     Name of the variable.
 * @param value
 *     Value to be stored.
 * @param link
 *     Name of a node to get the value from.
 */
Uniform::Uniform(string type,
                 string name,
                 GLfloat value,
                 string link) {
	
	// Initialize
	this->type = type;
	this->name = name;
	this->value = value;
	this->link = link;
	init();
	verify();
}


/**
 * Creates a new %Uniform from an XML tag.
 * 
 * @param tag
 *     XML tag.
 */
Uniform::Uniform(const Tag &tag) {
	
	// Initialize
	tag.get("type", type);
	tag.get("name", name);
	tag.get("value", value, false);
	tag.get("link", link, false);
	init();
	verify();
}


/**
 * Finds a Program node that is an ancestor of this node.
 */
void Uniform::associate() {
	
	Node *current;
	Texture *texture;
	string message;
	
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
		if (texture == NULL) {
			message = "[Gander,Uniform] Could not find texture with '";
			message += link + "' as name.";
			throw message.c_str();
		}
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
	location = glGetUniformLocation(program->getHandle(), name.c_str());
	if (location == -1)
		return;
}


/**
 * Initializes the %Uniform's attributes.
 */
void Uniform::init() {
	
	// Defaults
	className = "Uniform";
	this->program = NULL;
	
	// Conversions
	if (type.compare("float") == 0)
		this->valueType = GL_FLOAT;
	else
		this->valueType = GL_INT;
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
	types.insert("sampler1d");
	types.insert("sampler2d");
	types.insert("sampler3d");
}


/**
 * Checks if the uniform is a sampler type.
 */
bool Uniform::isSampler() {
	
	string type;
	
	// Compare strings
	type = Tag::tolower(this->type);
	return (type == "sampler1d"
	          || type == "sampler2d"
	          || type == "sampler3d");
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


/**
 * Resets the uniform variable in the program to 0.
 */
void Uniform::remove() {
	
	// Set value
/*
	if (valueType == GL_FLOAT)
		glUniform1f(location, 0.0f);
	else
		glUniform1i(location, 0);
*/
}


/**
 * Checks that the Uniform's attributes are acceptable.
 */
void Uniform::verify() {
	
	// Check if type is supported
	initTypes();
	if (!isSupported(this->type))
		throw "[Gander,Uniform] Type not supported.";
	
	// Check if sampler type has link
	if (isSampler() && link.empty())
		throw "[Gander,Uniform] Sampler types require link.";
}


/**
 * Forms a string from the object's attributes.
 */
string Uniform::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << " type='" << type << "'"
	       << " name='" << name << "'"
	       << " value='" << value << "'"
	       << " link='" << link << "'";
	return stream.str();
}


/*
 * Uniform.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
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
			ostringstream message;
			message << "[Uniform] Could not find texture with '" << link
			        << "'as name.";
			throw message.str().c_str();
		}
		value = texture->getUnit();
	}
}


/**
 * Sets the value of the variable in the program.
 */
void Uniform::apply() {
	
	// Set value
	if (isMatrix) {
		applyAsMatrix();
	} else {
		applyAsValue();
	}
}


void Uniform::applyAsMatrix() {
	
	switch (matrixType) {
	case MODELVIEW:
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		break;
	case PROJECTION:
		glGetFloatv(GL_PROJECTION_MATRIX, matrix);
		break;
	case MODELVIEW_PROJECTION:
		Transform::getModelViewProjectionMatrix(matrix);
		break;
	}
	glUniformMatrix4fv(location, 1, false, matrix);
}


void Uniform::applyAsValue() {
	
	switch (valueType) {
	case GL_FLOAT:
		glUniform1f(location, value);
		break;
	case GL_INT:
		glUniform1i(location, static_cast<int>(value));
		break;
	}
}


/**
 * Finds the variable's location in the program.
 * 
 * @throws const_char* if program cannot be found.
 * @throws const_char* if location for uniform cannot be found
 */
void Uniform::finalize() {
	
	// Check for no program
	if (program == NULL) {
		ostringstream message;
		message << "[Uniform] Program for uniform named '" << name
		        << "' cannot be found.";
		throw message.str().c_str();
	}
	
	// Look up location
	location = glGetUniformLocation(program->getHandle(), name.c_str());
	if (location == -1) {
		ostringstream message;
		message << "[Uniform] Location for uniform named '" << name
		        << "' cannot be found.";
		throw message.str().c_str();
	}
}


/**
 * Initializes the %Uniform's attributes.
 */
void Uniform::init() {
	
	// Defaults
	className = "Uniform";
	program = NULL;
	isMatrix = false;
	
	// Conversions
	if (type == "float") {
		valueType = GL_FLOAT;
	} else if (type == "mat4") {
		initAsMatrix();
	} else {
		valueType = GL_INT;
	}
}


void Uniform::initAsMatrix() {
	
	isMatrix = true;
	
	if (link == "modelview") {
		matrixType = MODELVIEW;
	} else if (link == "projection") {
		matrixType = PROJECTION;
	} else if (link == "modelviewprojection") {
		matrixType = MODELVIEW_PROJECTION;
	} else {
		throw "[Uniform] Matrix not supported.";
	}
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
	types.insert("mat4");
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
	if (!isSupported(type))
		throw "[Uniform] Type not supported.";
	
	// Check if sampler type has link
	if (isSampler() && link.empty())
		throw "[Uniform] Sampler types require link to texture.";
}


/**
 * Forms a string from the object's attributes.
 */
string Uniform::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << " type='" << type << "'"
	       << " name='" << name << "'";
	if (!isMatrix) {
		stream << " value='" << value << "'";
	}
	stream << " link='" << link << "'"
	       << " location='" << location << "'";
	return stream.str();
}


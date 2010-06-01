/*
 * Uniform.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Uniform.hpp"


/** Initializes "program", "type", "name", "link", and "suppress" attributes. */
Uniform::Uniform(const Tag &tag) : Applicable(tag) {
	
	// Initialize
	program = NULL;
	tag.get("type", type);
	tag.get("name", name, true, false);
	tag.get("link", link, false, false);
}


/** Finds a Program node that is an ancestor of this node.
 * 
 * @throws NodeException if program cannot be found.
 */
void Uniform::associate() {
	
	// Look for a Program ancestor
	program = Program::find(parent);
	if (program == NULL) {
		NodeException e(tag);
		e << "Program for uniform named '" << name << "' cannot be found.";
		throw e;
	}
}


/** Finds the variable's location in the program.
 * 
 * @throws NodeException if location for uniform cannot be found
 */
void Uniform::finalize() {
	
	// Look up location
	location = glGetUniformLocation(program->getHandle(), name.c_str());
	if (location == -1 && !isSuppressed()) {
		NodeException e(tag);
		e << "[Uniform] Location for uniform '" << name << "' cannot be found.";
		throw e;
	}
}


/** Forms a string from the object's attributes. */
string Uniform::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << " name='" << name << "'"
	       << " location='" << location << "'";
	if (!link.empty()) {
		stream << " link='" << link << "'";
	}
	return stream.str();
}


/** @return True if the uniform was suppressed. */
bool Uniform::wasSuppressed() const {
	
	return (location == -1) && isSuppressed();
}


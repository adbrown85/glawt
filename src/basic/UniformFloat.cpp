/*
 * UniformFloat.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformFloat.hpp"


UniformFloat::UniformFloat(const Tag &tag) :
                           Uniform(tag) {
	
	tag.get("value", value, false);
}


void UniformFloat::apply() {
	
	if (location != -1)
		glUniform1f(location, value);
}


void UniformFloat::associate() {
	
	Uniform::associate();
	
	Node *node;
	pair<string,string> linkNameKey;
	string linkValue;
	
	// Doesn't have link
	if (link.empty())
		return;
	
	// Split up the link
	linkNameKey = Text::split(link, '.');
	
	// Find the link
	node = Nameable::search(findRoot(this), linkNameKey.first);
	if (node == NULL) {
		NodeException e(tag);
		e << "[UniformVector] Could not find node named '" << link << "'.";
		throw e;
	}
	
	// Get the value
	linkValue = node->getAttribute(linkNameKey.second);
	if (linkValue.empty()) {
		NodeException e(tag);
		e << "[UniformVector] Value for '" << link << "' is empty.";
		throw e;
	}
	
	// Set the value
	this->value = atof(linkValue.c_str());
}


bool UniformFloat::setAttribute(pair<string,string> attrib) {
	
	if (Text::toLower(attrib.first) == "value") {
		value = atof(attrib.second.c_str());
		return true;
	}
	return false;
}


string UniformFloat::toString() const {
	
	ostringstream stream;
	
	stream << Uniform::toString();
	stream << " value='" << value << "'";
	return stream.str();
}


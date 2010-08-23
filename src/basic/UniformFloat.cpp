/*
 * UniformFloat.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformFloat.hpp"


UniformFloat::UniformFloat(const Tag &tag) : Uniform(tag) {
	
	tag.get("value", value, false);
}


void UniformFloat::apply() {
	
	if (hasLocation())
		glUniform1f(getLocation(), value);
}


void UniformFloat::associate() {
	
	Uniform::associate();
	
	Node *node;
	pair<string,string> linkNameKey;
	string linkValue;
	
	// Doesn't have link
	if (!hasLink())
		return;
	
	// Split up the link
	linkNameKey = Text::split(getLink(), '.');
	
	// Find the link
	node = Scout<Node>::search(findRoot(this), linkNameKey.first);
	if (node == NULL) {
		NodeException e(tag);
		e << "[UniformVector] Could not find '" << linkNameKey.first << "'.";
		throw e;
	}
	
	// Get the value
	linkValue = node->getAttribute(linkNameKey.second);
	if (linkValue.empty()) {
		NodeException e(tag);
		e << "[UniformVector] Value for '" << getLink() << "' is empty.";
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


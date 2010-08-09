/*
 * UniformVector.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformVector.hpp"


/** Initializes the type and value (or link).
 * 
 * @throws NodeException if @e type is not supported.
 * @throws NodeException if @e value or @e link not specified.
 */
UniformVector::UniformVector(const Tag &tag) : Uniform(tag) {
	
	// Type
	if (type == "vec3") {
		size = 3;
	} else if (type == "vec4") {
		size = 4;
	} else {
		NodeException e(tag);
		e << "[UniformVector] '" << type << "' not supported.";
		throw e;
	}
	
	// Value or link
	if (!tag.get("value", value, false)) {
		if (!tag.get("link", link, false)) {
			NodeException e(tag);
			e << "[UniformVector] Need 'value' or 'link' attribute.";
			throw e;
		}
	}
	
	// Other
	transformable = NULL;
}


void UniformVector::associate() {
	
	Uniform::associate();
	
	Node *node;
	
	// Doesn't have link
	if (link.empty())
		return;
	
	// Find the link
	node = Nameable::search(findRoot(this), link);
	if (node == NULL) {
		NodeException e(tag);
		e << "[UniformVector] Could not find node named '" << link << "'.";
		throw e;
	}
	
	// Make it transformable
	transformable = dynamic_cast<Transformable*>(node);
	if (transformable == NULL) {
		NodeException e(tag);
		e << "[UniformVector] Node '" << link << "' is not transformable.";
		throw e;
	}
}


/** @throws NodeException if unexpeted size is encountered. */
void UniformVector::apply() {
	
	if (location == -1)
		return;
	
	// Update values
	if (transformable != NULL) {
		transformable->getPosition().toArray(value);
		fireEvent(NodeEvent(this, NodeEvent::MODIFY));
	}
	
	// Set values
	switch (size) {
	case 3: glUniform3fv(location, 1, value); break;
	case 4: glUniform4fv(location, 1, value); break;
	default:
		NodeException e(tag);
		e << "[UniformVector] Unexpected size while applying.";
		throw e;
	}
}


string UniformVector::toString() const {
	
	ostringstream stream;
	
	stream << Uniform::toString();
	stream << " value='" << value[0];
	for (int i=1; i<size; ++i)
		stream << " " << value[i];
	stream << "'";
	if (!link.empty())
		stream << " link='" << link << "'";
	return stream.str();
}


/*
 * UniformVector.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformVector.hpp"


/** Initializes the type and value (or link).
 * 
 * @throw NodeException if @e type is not supported.
 * @throw NodeException if @e value or @e link not specified.
 */
UniformVector::UniformVector(const Tag &tag) : Uniform(tag) {
	
	// Type
	if (getType() == "vec3") {
		size = 3;
	} else if (getType() == "vec4") {
		size = 4;
	} else {
		NodeException e(tag);
		e << "[UniformVector] '" << getType() << "' not supported.";
		throw e;
	}
	
	// Value or link
	if (!tag.get("value", value, false)) {
		if (!hasLink()) {
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
	
	// Doesn't have link
	if (!hasLink())
		return;
	
	// Find the link
	transformable = Scout<Transformable>::search(findRoot(this), getLink());
	if (transformable == NULL) {
		NodeException e(tag);
		e << "[UniformVector] Could not find node '" << getLink() << "'.";
		throw e;
	}
}


/** @throw NodeException if unexpected size is encountered. */
void UniformVector::apply() {
	
	if (!hasLocation())
		return;
	
	// Update values
	if (transformable != NULL) {
		transformable->getPosition().toArray(value);
		fireEvent(NodeEvent(this, NodeEvent::MODIFY));
	}
	
	// Set values
	switch (size) {
	case 3: glUniform3fv(getLocation(), 1, value); break;
	case 4: glUniform4fv(getLocation(), 1, value); break;
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
	return stream.str();
}


/*
 * UniformVector.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformVector.hpp"


UniformVector::UniformVector(const Tag &tag) :
                             Uniform(tag) {
	
	// Initialize
	tag.get("value", value, true);
	if (type == "vec3") {
		size = 3;
	} else if (type == "vec4") {
		size = 4;
	} else {
		ostringstream msg;
		msg << tag.getLine() << ": ";
		msg << "[UniformVector] '" << type << "' not supported.";
		throw msg.str().c_str();
	}
}


void UniformVector::apply() {
	
	switch (size) {
	case 3: glUniform3fv(location, 1, value); break;
	case 4: glUniform4fv(location, 1, value); break;
	default:
		throw "[UniformVector] Unexpected size found while applying.";
	}
}


string UniformVector::toString() const {
	
	ostringstream stream;
	
	stream << Uniform::toString();
	stream << " value='" << value[0];
	for (int i=1; i<size; ++i) {
		stream << " " << value[i];
	}
	stream << "'";
	return stream.str();
}


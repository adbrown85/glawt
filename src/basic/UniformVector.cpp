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
		Exception e;
		e << tag.getFilename() << ":" << tag.getLine() << ": ";
		e << "[UniformVector] '" << type << "' not supported.";
		throw e;
	}
}


void UniformVector::apply() {
	
	if (location == -1)
		return;
	
	switch (size) {
	case 3: glUniform3fv(location, 1, value); break;
	case 4: glUniform4fv(location, 1, value); break;
	default:
		throw Exception("[UniformVector] Unexpected size while applying.");
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


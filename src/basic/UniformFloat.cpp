/*
 * UniformFloat.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformFloat.hpp"


UniformFloat::UniformFloat(const Tag &tag) :
                           Uniform("UniformFloat", tag) {
	
	tag.get("value", value, false);
}


void UniformFloat::apply() {
	
	glUniform1f(location, value);
}


string UniformFloat::toString() const {
	
	ostringstream stream;
	
	stream << Uniform::toString();
	stream << " value='" << value << "'";
	return stream.str();
}


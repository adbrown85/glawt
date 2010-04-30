/*
 * UniformInt.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformInt.hpp"


UniformInt::UniformInt(const Tag &tag) :
                       Uniform("UniformInt", tag) {
	
	tag.get("value", value, false);
}


void UniformInt::apply() {
	
	glUniform1i(location, value);
}


string UniformInt::toString() const {
	
	ostringstream stream;
	
	stream << Uniform::toString();
	stream << " value='" << value << "'";
	return stream.str();
}


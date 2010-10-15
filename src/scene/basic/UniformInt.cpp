/*
 * UniformInt.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformInt.hpp"


UniformInt::UniformInt(const Tag &tag) : Uniform(tag) {
	
	tag.get("value", value, true);
}


void UniformInt::apply() {
	
	if (hasLocation())
		glUniform1i(getLocation(), value);
}


string UniformInt::toString() const {
	
	ostringstream stream;
	
	stream << Uniform::toString();
	stream << " value='" << value << "'";
	return stream.str();
}


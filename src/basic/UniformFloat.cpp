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


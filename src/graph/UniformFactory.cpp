/*
 * UniformFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformFactory.hpp"


/**
 * Creates a uniform variable from a tag.
 * 
 * @param tag XML tag with "type" attribute.
 * @return pointer to a uniform variable.
 * @throws const_char* if type is not supported.
 */
Uniform* UniformFactory::create(const Tag &tag) {
	
	string type;
	
	// Get type
	tag.get("type", type);
	
	// Create based on type
	if (type == "int")
		return new UniformInt(tag);
	else if (type == "float")
		return new UniformFloat(tag);
	else if (type == "mat4" || type == "mat3")
		return new UniformMatrix(tag);
	else if (type == "sampler1d" || type == "sampler2d" || type == "sampler3d")
		return new UniformSampler(tag);
	else if (type == "vec3" || type == "vec4")
		return new UniformVector(tag);
	else {
		ostringstream msg;
		msg << "[UniformFactory] Type '" << type
		    << "' not supported.";
		throw msg.str().c_str();
	}
}


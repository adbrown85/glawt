/*
 * UniformFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformFactory.hpp"


UniformFactory::UniformFactory() {
	
	// Matrices
	matrices.insert("mat3");
	matrices.insert("mat4");
	
	// Samplers
	samplers.insert("sampler1d");
	samplers.insert("sampler2d");
	samplers.insert("sampler3d");
	samplers.insert("isampler1d");
	samplers.insert("isampler2d");
	samplers.insert("isampler3d");
	samplers.insert("usampler1d");
	samplers.insert("usampler2d");
	samplers.insert("usampler3d");
	
	// Vectors
	vectors.insert("vec3");
	vectors.insert("vec4");
}


/**
 * Creates a uniform variable from a tag.
 * 
 * @param tag XML tag with "type" attribute.
 * @return pointer to a uniform variable.
 * @throws const_char* if type is not supported.
 */
Node* UniformFactory::create(const Tag &tag) {
	
	string type;
	
	// Create based on type
	tag.get("type", type);
	if (type == "int")
		return new UniformInt(tag);
	else if (type == "float")
		return new UniformFloat(tag);
	else if (isMatrix(type))
		return new UniformMatrix(tag);
	else if (isSampler(type))
		return new UniformSampler(tag);
	else if (isVector(type))
		return new UniformVector(tag);
	else {
		ostringstream msg;
		msg << "[UniformFactory] Type '" << type
		    << "' not supported.";
		throw msg.str().c_str();
	}
}


set<string> UniformFactory::getClasses() {
	
	set<string> classes;
	set<string>::iterator it;
	
	for (it=matrices.begin(); it!=matrices.end(); ++it)
		classes.insert(*it);
	for (it=samplers.begin(); it!=samplers.end(); ++it)
		classes.insert(*it);
	for (it=vectors.begin(); it!=vectors.end(); ++it)
		classes.insert(*it);
	return classes;
}


bool UniformFactory::isMatrix(const string &type) {
	
	set<string>::iterator it;
	
	it = matrices.find(type);
	return it != matrices.end();
}


bool UniformFactory::isSampler(const string &type) {
	
	set<string>::iterator it;
	
	it = samplers.find(type);
	return it != samplers.end();
}


bool UniformFactory::isVector(const string &type) {
	
	set<string>::iterator it;
	
	it = vectors.find(type);
	return it != vectors.end();
}


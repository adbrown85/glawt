/*
 * ShaderFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ShaderFactory.hpp"


ShaderFactory::ShaderFactory() {
	
	// Tags
	tags.insert("program");
	tags.insert("shader");
	tags.insert("uniform");
	
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


Node* ShaderFactory::create(const Tag &tag) const {
	
	if (tag.name == "program")
		return new Program(tag);
	else if (tag.name == "shader")
		return new Shader(tag);
	else if (tag.name == "uniform")
		return createUniform(tag);
	else {
		throw "[ShaderFactory] Tag not supported by this factory.";
	}
}


/**
 * Creates a uniform variable from a tag.
 * 
 * @param tag XML tag with "type" attribute.
 * @return pointer to a uniform variable.
 * @throws const_char* if type is not supported.
 */
Node* ShaderFactory::createUniform(const Tag &tag) const {
	
	string type;
	
	// Create based on type
	tag.get("type", type);
	if (type == "int")
		return new UniformInt(tag);
	else if (type == "float")
		return new UniformFloat(tag);
	else if (isUniformMatrix(type))
		return new UniformMatrix(tag);
	else if (isUniformSampler(type))
		return new UniformSampler(tag);
	else if (isUniformVector(type))
		return new UniformVector(tag);
	else {
		ostringstream msg;
		msg << "[ShaderFactory] Uniform type '" << type
		    << "' not supported.";
		throw msg.str().c_str();
	}
}


bool ShaderFactory::isUniformMatrix(const string &type) const {
	
	set<string>::iterator it;
	
	it = matrices.find(type);
	return it != matrices.end();
}


bool ShaderFactory::isUniformSampler(const string &type) const {
	
	set<string>::iterator it;
	
	it = samplers.find(type);
	return it != samplers.end();
}


bool ShaderFactory::isUniformVector(const string &type) const {
	
	set<string>::iterator it;
	
	it = vectors.find(type);
	return it != vectors.end();
}


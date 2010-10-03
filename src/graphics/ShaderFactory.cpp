/*
 * ShaderFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ShaderFactory.hpp"
map<string,GLuint> ShaderFactory::shaders;
ShaderBuilder ShaderFactory::builder;


GLuint ShaderFactory::create(const string &type, const string &filename) {
	
	map<string,GLuint>::iterator it;
	
	// Check if already made
	it = shaders.find(filename);
	if (it != shaders.end()) {
		return it->second;
	}
	
	// Build it
	builder.build(type, filename);
	shaders[filename] = builder.getHandle();
	return builder.getHandle();
}


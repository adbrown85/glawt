/*
 * BasicFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BasicFactory.hpp"
bool BasicFactory::loaded=false;
map<string,BasicFactory::kind_t> BasicFactory::kinds;


void BasicFactory::install() {
	
	// Tags
	Factory::install("cube", &createCube);
	Factory::install("program", &createProgram);
	Factory::install("scale", &createScale);
	Factory::install("shader", &createShader);
	Factory::install("square", &createSquare);
	Factory::install("texture", &createTexture);
	Factory::install("translate", &createTranslate);
	Factory::install("uniform", &createUniform);
}


Node* BasicFactory::createCube(const Tag &tag) {
	
	return new Cube(tag);
}


Node* BasicFactory::createProgram(const Tag &tag) {
	
	return new Program(tag);
}


Node* BasicFactory::createScale(const Tag &tag) {
	
	return new Scale(tag);
}


Node* BasicFactory::createShader(const Tag &tag) {
	
	return new Shader(tag);
}


Node* BasicFactory::createSquare(const Tag &tag) {
	
	return new Square(tag);
}


Node* BasicFactory::createTexture(const Tag &tag) {
	
	string extension, filename;
	
	// Create based on file extension
	tag.get("file", filename, false, false);
	extension = FileUtility::getExtension(filename);
	if (Text::toLower(extension) == "vlb") {
		return new Texture3D(tag);
	} else {
		return new Texture2D(tag);
	}
}


Node* BasicFactory::createTranslate(const Tag &tag) {
	
	return new Translation(tag);
}


Node* BasicFactory::createUniform(const Tag &tag) {
	
	string type;
	
	// Initialize
	load();
	tag.get("type", type);
	
	// Create based on kind
	switch (kinds.find(type)->second) {
	case INT:
		return new UniformInt(tag);
	case FLOAT:
		return new UniformFloat(tag);
	case MATRIX:
		return new UniformMatrix(tag);
	case SAMPLER:
		return new UniformSampler(tag);
	case VECTOR:
		return new UniformVector(tag);
	default:
		ostringstream msg;
		msg << "[BasicFactory] Uniform type '" << type
		    << "' not supported.";
		throw msg.str().c_str();
	}
}


void BasicFactory::load() {
	
	// Check if already loaded
	if (loaded)
		return;
	loaded = true;
	
	// Map types back to kinds
	kinds["int"] = INT;
	kinds["float"] = FLOAT;
	kinds["mat3"] = MATRIX;
	kinds["mat4"] = MATRIX;
	kinds["sampler1d"] = SAMPLER;
	kinds["sampler2d"] = SAMPLER;
	kinds["sampler3d"] = SAMPLER;
	kinds["usampler1d"] = SAMPLER;
	kinds["usampler2d"] = SAMPLER;
	kinds["usampler3d"] = SAMPLER;
	kinds["vec3"] = VECTOR;
	kinds["vec4"] = VECTOR;
}


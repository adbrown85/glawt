/*
 * BasicFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BasicFactory.hpp"
bool BasicFactory::installed=false;
map<string,BasicFactory::kind_t> BasicFactory::kinds;


void BasicFactory::install() {
	
	// Check if already called
	if (installed)
		return;
	installed = true;
	
	// Tags
	Factory::install("box", &createBox);
	Factory::install("cone", &createCone);
	Factory::install("cube", &createCube);
	Factory::install("disk", &createDisk);
	Factory::install("group", &createGroup);
	Factory::install("instance", &createInstance);
	Factory::install("light", &createLight);
	Factory::install("line", &createLine);
	Factory::install("program", &createProgram);
	Factory::install("rotate", &createRotate);
	Factory::install("scale", &createScale);
	Factory::install("shader", &createShader);
	Factory::install("square", &createSquare);
	Factory::install("texture", &createTexture);
	Factory::install("translate", &createTranslate);
	Factory::install("uniform", &createUniform);
	Factory::install("wireframe", &createWireframe);
	
	// Map uniform types back to kinds
	kinds["int"] = INT;
	kinds["float"] = FLOAT;
	kinds["float[]"] = FLOAT_ARRAY;
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


Node* BasicFactory::createBox(const Tag &tag) {return new Box(tag);}

Node* BasicFactory::createCone(const Tag &tag) {return new Cone(tag);}

Node* BasicFactory::createCube(const Tag &tag) {return new Cube(tag);}

Node* BasicFactory::createDisk(const Tag &tag) {return new Disk(tag);}

Node* BasicFactory::createGroup(const Tag &t) {return new Group(t);}

Node* BasicFactory::createInstance(const Tag &t) {return new Instance(t);}

Node* BasicFactory::createLight(const Tag &tag) {return new Light(tag);}

Node* BasicFactory::createLine(const Tag &tag) {return new Line(tag);}

Node* BasicFactory::createProgram(const Tag &tag) {return new Program(tag);}

Node* BasicFactory::createRotate(const Tag &tag) {return new Rotate(tag);}

Node* BasicFactory::createScale(const Tag &tag) {return new Scale(tag);}

Node* BasicFactory::createShader(const Tag &tag) {return new Shader(tag);}

Node* BasicFactory::createSquare(const Tag &tag) {return new Square(tag);}


Node* BasicFactory::createTexture(const Tag &tag) {
	
	string extension, filename;
	
	// Create based on file extension
	tag.get("file", filename, false, false);
	extension = Path::getExtension(filename);
	if (Text::toLower(extension) == "vlb") {
		return new Texture3D(tag);
	} else {
		return new Texture2D(tag);
	}
}


Node* BasicFactory::createTranslate(const Tag &t) {return new Translate(t);}


Node* BasicFactory::createUniform(const Tag &tag) {
	
	kind_t kind;
	map<string,kind_t>::iterator it;
	string type;
	
	// Get type
	tag.get("type", type);
	it = kinds.find(type);
	if (it == kinds.end()) {
		NodeException e(tag);
		e << "[BasicFactory] Uniform type '" << type << "' not supported.";
		throw e;
	}
	
	// Create based on kind
	kind = it->second;
	switch (kind) {
	case INT:
		return new UniformInt(tag);
	case FLOAT:
		return new UniformFloat(tag);
	case FLOAT_ARRAY:
		return new UniformFloatArray(tag);
	case MATRIX:
		return new UniformMatrix(tag);
	case SAMPLER:
		return new UniformSampler(tag);
	case VECTOR:
		return new UniformVector(tag);
	default:
		NodeException e(tag);
		e << "[BasicFactory] Unexpected error making uniform.";
		throw e;
	}
}


Node* BasicFactory::createWireframe(const Tag &tag) {
	
	return new Wireframe(tag);
}


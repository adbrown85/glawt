/*
 * Uniform.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Uniform.hpp"


/** Initialize attributes.
 * 
 * @throws NodeException if name not specified.
 */
Uniform::Uniform(const Tag &tag) : Node(tag), Nameable(tag) {
	
	// From tag
	tag.get("type", type);
	tag.get("link", link, false, false);
	
	// Other
	program = NULL;
	location = 0;
	
	// Check
	if (!hasName()) {
		NodeException e(getTag());
		e << "[Uniform] Must have name.";
		throw e;
	}
}


/** Finds a Program node that is an ancestor of this node.
 * 
 * @throws NodeException if program cannot be found.
 */
void Uniform::associate() {
	
	// Look for a Program ancestor
	program = Program::find(parent);
	if (program == NULL) {
		NodeException e(tag);
		e << "[Uniform] Program for '" << getName() << "' cannot be found.";
		throw e;
	}
}


/** Finds the variable's location in the program.
 * 
 * @throws NodeException if location for uniform cannot be found
 */
void Uniform::finalize() {
	
	// Look up location
	location = glGetUniformLocation(program->getHandle(), getName().c_str());
	if (location == -1 && !isSuppressed()) {
		NodeException e(tag);
		e << "[Uniform] Location for '" << getName() << "' cannot be found.";
		throw e;
	}
}


/** @return Names and types of all the active uniforms in @e program. */
map<string,UniformInfo> Uniform::getUniformsFor(Program *program) {
	
	char *buffer;
	GLint count, size;
	map<string,UniformInfo> catalog;
	GLenum type;
	UniformInfo info;
	
	// Get count and size
	glGetProgramiv(program->getHandle(), GL_ACTIVE_UNIFORMS, &count);
	glGetProgramiv(program->getHandle(), GL_ACTIVE_UNIFORM_MAX_LENGTH, &size);
	
	// Make buffer
	buffer = new char[size+1];
	
	// Get info
	for (int i=0; i<count; ++i) {
		glGetActiveUniform(program->getHandle(),                 // program
		                   i,                                    // index
		                   size,                                 // bufSize
		                   NULL,                                 // length
		                   &(info.count),                        // elements
		                   &(info.type),                         // type
		                   buffer);                              // name
		catalog[buffer] = info;
	}
	return catalog;
}


/** @return Text describing the type of a uniform variable .*/
string Uniform::getTypeNameFor(GLenum type) {
	
	switch (type) {
	case GL_FLOAT:             return "float";
	case GL_FLOAT_VEC2:        return "vec2";
	case GL_FLOAT_VEC3:        return "vec3";
	case GL_FLOAT_VEC4:        return "vec4";
	case GL_INT:               return "int";
	case GL_INT_VEC2:          return "ivec2";
	case GL_INT_VEC3:          return "ivec3";
	case GL_INT_VEC4:          return "ivec4";
	case GL_BOOL:              return "bool";
	case GL_BOOL_VEC2:         return "bvec2";
	case GL_BOOL_VEC3:         return "bvec3";
	case GL_BOOL_VEC4:         return "bvec4";
	case GL_FLOAT_MAT2:        return "mat2";
	case GL_FLOAT_MAT3:        return "mat3";
	case GL_FLOAT_MAT4:        return "mat4";
	case GL_SAMPLER_1D:        return "sampler1D";
	case GL_SAMPLER_2D:        return "sampler2D";
	case GL_SAMPLER_3D:        return "sampler3D";
	case GL_SAMPLER_CUBE:      return "samplerCube";
	case GL_SAMPLER_1D_SHADOW: return "sampler1DShadow";
	case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
	}
}


/** @return True if the type is @e mat2, @e mat3, or @e mat3. */
bool Uniform::isMatrixType(GLenum type) {
	
	switch (type) {
	case GL_FLOAT_MAT2:
	case GL_FLOAT_MAT3:
	case GL_FLOAT_MAT4:
		return true;
	default:
		return false;
	}
}


/** Forms a string from the object's attributes. */
string Uniform::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << " name='" << getName() << "'"
	       << " location='" << location << "'";
	if (hasLink()) {
		stream << " link='" << link << "'";
	}
	return stream.str();
}


/** @return True if the uniform was suppressed. */
bool Uniform::wasSuppressed() const {
	
	return (location == -1) && isSuppressed();
}


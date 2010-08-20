/*
 * ShaderBuilder.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ShaderBuilder.hpp"


/** Builds a shader from @e filename. */
void ShaderBuilder::build(const string &type, const string &filename) {
	
	// Store
	this->type = type;
	this->filename = filename;
	
	// Build
	create();
	load();
	compile();
}


/** Requests a handle to a new GLSL shader of the correct type.
 * 
 * @throws Exception if <i>type</i> is not supported.
 */
void ShaderBuilder::create() {
	
	// Create shader of correct type
	if (type == "fragment") {
		handle = glCreateShader(GL_FRAGMENT_SHADER);
	} else if (type == "vertex") {
		handle = glCreateShader(GL_VERTEX_SHADER);
	} else {
		Exception e;
		e << "[Shader] Type not supported.";
		throw e;
	}
}


/** Loads a file into the Shader's source array and passes it to OpenGL.
 * 
 * @throws Exception from CodeLoader.
 */
void ShaderBuilder::load() {
	
	Code::iterator it;
	CodeLoader loader;
	const char **source;
	int i, length;
	
	// Load file
	loader.parse(filename);
	code = loader.getCode();
	
	// Copy to source array
	length = code.size();
	source = new const char*[length];
	for (it=code.begin(); it!=code.end(); ++it) {
		i = distance(code.begin(), it);
		source[i] = it->text.c_str();
	}
	
	// Pass to OpenGL
	glShaderSource(handle, length, source, NULL);
}


/** Compiles the shader and prints the log.
 * 
 * @throws Exception if the shader doesn't compile.
 */
void ShaderBuilder::compile() {
	
	GLchar *log;
	GLint compiled, count, returned;
	
	// Compile
	glCompileShader(handle);
	
	// Print log
	glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &count);
	log = new GLchar[count+1];
	glGetShaderInfoLog(handle, count, &returned, log);
	log[returned] = '\0';
	Error::print(log, code);
	delete[] log;
	
	// Check
	glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		Exception e;
		e << "[ShaderBuilder] '" << filename << "' did not compile." << endl;
		throw e;
	}
}


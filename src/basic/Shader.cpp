/*
 * Shader.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Shader.hpp"


/** Creates a new %Shader from an XML tag.
 * 
 * @param tag XML tag with "type" and "file" attributes.
 * @throws NodeException if extension not recognized as a type.
 */
Shader::Shader(const Tag &tag) : Node(tag) {
	
	// Initialize attributes
	length = 0;
	handle = 0;
	source = NULL;
	tag.get("file", filename, true, false);
	tag.get("type", type, false);
	
	// Check type or try to guess from extension
	if (type != "") {
		type = Text::toLower(type);
	} else {
		string extension = Text::toLower(Path::getExtension(filename));
		if (extension == "frag")
			this->type = "fragment";
		else if (extension == "vert")
			this->type = "vertex";
		else {
			NodeException e(tag);
			e << "[Shader] Extension '" << extension
			  << "' not recognized as type.";
			throw e;
		}
	}
}


/** Cleans up the source array allocated by the %Shader object.
 */
Shader::~Shader() {
	
	// Clean up
	if (source != NULL)
		delete[] source;
}


/** Attaches the shader to a program and compiles the shader.
 * 
 * @throws NodeException from create()
 * @throws NodeException from load()
 * @throws NodeException from compile()
 */
void Shader::associate() {
	
	Program *program;
	
	// Attach and compile shader if found
	program = Program::find(parent);
	if (program != NULL) {
		if (handle == 0) {
			create();
			load();
			compile();
		}
		glAttachShader(program->getHandle(), handle);
		program->addCode(handle, &preprocessor);
	}
}


/** Compiles the shader and prints the log..
 * 
 * @throws NodeException if the shader doesn't compile.
 */
void Shader::compile() {
	
	GLint compiled=0;
	
	// Compile shader
	glCompileShader(handle);
	glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);
	log();
	if (!compiled) {
		NodeException e(tag);
		e << "[Shader] '" << filename << "' did not compile." << endl;
		throw e;
	}
}


/** Requests a handle to a new GLSL shader of the correct type.
 * 
 * @throws NodeException if <i>type</i> is not supported.
 */
void Shader::create() {
	
	// Create shader of correct type
	if (type == "fragment")
		handle = glCreateShader(GL_FRAGMENT_SHADER);
	else if (type == "vertex")
		handle = glCreateShader(GL_VERTEX_SHADER);
	else {
		NodeException e(tag);
		e << "[Shader] Type not supported.";
		throw e;
	}
}


/** Prints the file stored in the source array. */
void Shader::list() const {
	
	// Print
	for (int i=0; i<length; i++)
		cout << source[i];
}


/** Loads a file into the Shader's source array and passes it to OpenGL.
 * 
 * @throws NodeException if Preprocessor threw an exception.
 */
void Shader::load() {
	
	vector<string> lines;
	
	// Load file
	try {
		preprocessor.setFilename(filename);
		preprocessor.start();
		lines = preprocessor.getLines();
	} catch (Exception &ex) {
		NodeException e(tag);
		e << ex;
		throw e;
	}
	
	// Copy to source array
	length = lines.size();
	source = new const char*[length];
	for (int i=0; i<length; ++i) {
		source[i] = lines[i].c_str();
	}
	
	// Pass to OpenGL
	glShaderSource(handle, length, source, NULL);
}


/** Prints the log for this shader. */
void Shader::log() const {
	
	GLchar *log;
	GLint count=0, returned=0;
	
	// Get length
	glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &count);
	
	// Get the text
	log = new GLchar[count+1];
	glGetShaderInfoLog(handle, count, &returned, log);
	log[returned] = '\0';
	Error::print(log, handle, preprocessor);
	
	// Finish
	delete[] log;
}


/** Forms a string from the object's attributes. */
string Shader::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << " type='" << type << "'"
	       << " file='" << filename << "'"
	       << " handle='" << handle << "'";
	return stream.str();
}


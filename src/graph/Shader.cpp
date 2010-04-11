/*
 * Shader.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Shader.hpp"


/**
 * Initializes an empty %Shader object.
 */
Shader::Shader(string type,
               string filename) {
	
	// Initialize
	init();
	this->type = type;
	this->filename = filename;
}


/**
 * Creates a new %Shader from an XML tag.
 * 
 * @param tag XML tag with "type" and "file" attributes.
 */
Shader::Shader(const Tag &tag) {
	
	// Initialize
	init();
	tag.get("file", filename);
	if (!tag.get("type", type, false))
		initType();
}


/**
 * Cleans up the source array allocated by the %Shader object.
 */
Shader::~Shader() {
	
	// Clean up
	if (source != NULL)
		delete[] source;
}


/**
 * Attaches the shader to a program and compiles the shader.
 */
void Shader::associate() {
	
	Node *current;
	Program *program;
	
	// Look for parent program
	current = parent;
	while (current != NULL) {
		program = dynamic_cast<Program*>(current);
		if (program != NULL)
			break;
		current = current->getParent();
	}
	
	// Attach and compile shader if found
	if (program != NULL) {
		create();
		load();
		glAttachShader(program->getHandle(), handle);
		compile();
	}
}


/**
 * Compiles the shader.  Prints the log and exits if unsuccessful.
 * 
 * @throws const_char* if the shader doesn't compile.
 */
void Shader::compile() {
	
	GLint compiled=0;
	
	// Compile shader
	glCompileShader(handle);
	
	// Attach shader to program if successful
	glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);
	log();
	if (!compiled) {
		ostringstream message;
		message << "[Shader] '" << filename << "' did not compile." << endl;
		throw message.str().c_str();
	}
}


/**
 * Creates a GLSL shader.
 */
void Shader::create() {
	
	// Check if already created
	if (handle != 0)
		return;
	
	// Create shader of correct type
	if (type == "fragment")
		handle = glCreateShader(GL_FRAGMENT_SHADER);
	else if (type == "vertex")
		handle = glCreateShader(GL_VERTEX_SHADER);
	else
		throw "[Shader] Type not supported.";
}


/**
 * Initializes the %Shader's attributes.
 */
void Shader::init() {
	
	className = "Shader";
	this->length = 0;
	this->handle = 0;
	this->source = NULL;
}


/**
 * Initializes the type by guessing from the file's extension.
 */
void Shader::initType() {
	
	int pos;
	string extension;
	
	// Check extension for ".frag" or ".vert"
	pos = filename.find_last_of('.');
	extension = filename.substr(pos);
	if (extension == ".frag")
		type = "fragment";
	else if (extension == ".vert")
		type = "vertex";
	else {
		ostringstream message;
		message << "[Shader] Extension '"
		        << extension << "' not recognized as type.\n";
		message << "[Shader] Use '.frag' or '.vert', "
		        << "or declare 'type' as 'fragment' or 'vertex'.";
		throw message.str().c_str();
	}
}


/**
 * Prints the file stored in the source array.
 */
void Shader::list() const {
	
	// Print
	for (int i=0; i<length; i++)
		cout << source[i];
}


/**
 * Loads a file into the Shader's source array and passes it to OpenGL.
 * 
 * @throws const_char* from load()
 */
void Shader::load() {
	
	vector<string> lines;
	
	// Load file
	preprocessor.setFilename(filename);
	preprocessor.start();
	lines = preprocessor.getLines();
	
	// Copy to source array
	length = lines.size();
	source = new const char*[length];
	for (int i=0; i<length; ++i) {
		source[i] = lines[i].c_str();
	}
	
	// Pass to OpenGL
	glShaderSource(handle, length, source, NULL);
}


/**
 * Prints the log for this shader.
 */
void Shader::log() const {
	
	GLchar *log;
	GLint count=0, returned=0;
	
	// Get length
	glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &count);
	
	// Print the log
	log = new GLchar[count+1];
	glGetShaderInfoLog(handle, count, &returned, log);
	log[returned] = '\0';
	if (strlen(log) != 0)
		cerr << log << endl;
	
	// Finish
	delete[] log;
}


/**
 * Forms a string from the object's attributes.
 */
string Shader::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << " type='" << type << "'"
	       << " file='" << filename << "'"
	       << " handle='" << handle << "'";
	return stream.str();
}


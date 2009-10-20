/*
 * Shader.cpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
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
 * @param tag
 *     XML tag.
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
 */
void Shader::compile() {
	
	GLint compiled=0;
	
	// Compile shader
	glCompileShader(handle);
	
	// Attach shader to program if successful
	glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		cerr << "[Gander,Shader] '"
		     << filename 
		     << "' did not compile." << endl;
		cerr << "[Gander,Shader] Printing log..." << endl;
		log();
		exit(1);
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
	if (type.compare("fragment") == 0)
		handle = glCreateShader(GL_FRAGMENT_SHADER);
	else if (type.compare("vertex") == 0)
		handle = glCreateShader(GL_VERTEX_SHADER);
	else
		throw "[Gander,Shader] Type not supported.";
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
		stringstream message;
		message << "[Gander,Shader] Extension '"
		        << extension << "' not recognized as type.\n";
		message << "[Gander,Shader] Use '.frag' or '.vert', "
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
		cout << source[i] << endl;
}



/**
 * Loads a file into the Shader's source array and passes it to OpenGL.
 */
void Shader::load() {
	
	ifstream file;
	string line, message;
	
	// Open file
	file.open(filename.c_str());
	if (!file) {
		message = "[Gander,Shader] Could not open '";
		message += filename;
		message += "'.";
		throw message.c_str();
	}
	
	// Load into vector
	getline(file, line);
	while (file) {
		lines.push_back(line);
		getline(file, line);
	}
	
	// Copy to source array
	length = lines.size();
	source = new const char*[length];
	for (int i=0; i<length; ++i)
		source[i] = lines[i].c_str();
	
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
	
	stringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << " type='" << type << "'"
	       << " file='" << filename << "'"
	       << " handle='" << handle << "'";
	return stream.str();
}


/*
 * Shader.cpp
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Shader.hpp"



/**
 * Creates a shader with an empty source array.
 */
Shader::Shader() {
	
	// Initialize
	source = NULL;
	clear();
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
 * Clears out the source and all other attributes.
 */
void Shader::clear() {
	
	// Clear source
	if (source != NULL) {
		delete[] source;
		source = NULL;
	}
	lines.clear();
	filename = "";
	length = 0;
	
	// Clear others
	name = 0;
	type = 'f';
}



/**
 * Compiles the shader.  Prints the log and exits if unsuccessful.
 */
void Shader::compile() {
	
	GLint compiled=0;
	
	// Compile shader
	glCompileShader(name);
	
	// Attach shader to program if successful
	log();
	glGetShaderiv(name, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		cerr << "  Shader: Did not compile." << endl;
		exit(1);
	}
}



/**
 * Creates the shader.
 * 
 * @param type
 *     Either 'f' for a fragment shader or 'v' for a vertex shader.
 */
void Shader::create() {
	
	GLenum typeEnum;
	
	// Convert type to enumeration
	switch (tolower(type)) {
		case 'f':
			typeEnum = GL_FRAGMENT_SHADER; break;
		case 'v':
			typeEnum = GL_VERTEX_SHADER; break;
		default:
			throw "Type not supported.";
	}
	
	// Create the shader
	name = glCreateShader(typeEnum);
}



/**
 * Loads a file into the Shader's source array.
 * 
 * @param type
 *     Either 'f' for a fragment shader or 'v' for a vertex shader.
 * @param filename
 *     Path to the file.
 */
void Shader::load(char type,
                  string filename) {
	
	// Initialize attributes
	clear();
	this->type = type;
	this->filename = filename;
	create();
	
	// Load source
	open();
	glShaderSource(name, length, source, NULL);
}



/**
 * Prints the log for this shader.
 */
void Shader::log() const {
	
	GLchar *log;
	GLint count=0, returned=0;
	
	// Get length
	glGetShaderiv(name, GL_INFO_LOG_LENGTH, &count);
	
	// Print the log
	log = new GLchar[count+1];
	glGetShaderInfoLog(name, count, &returned, log);
	log[returned] = '\0';
	if (strlen(log) != 0)
		cerr << log << endl;
	
	// Finish
	delete[] log;
}



/**
 * Opens the file and copies it into the object.
 */
void Shader::open() {
	
	ifstream inFile;
	string line;
	
	// Load file into vector
	inFile.open(filename.c_str());
	getline(inFile, line);
	while (inFile) {
		lines.push_back(line);
		getline(inFile, line);
	}
	
	// Copy to source array
	length = lines.size();
	source = new const char*[length];
	for (int i=0; i<length; ++i)
		source[i] = lines[i].c_str();
}



/**
 * Prints the file stored in the source array.
 */
void Shader::print() const {
	
	// Print
	for (int i=0; i<length; i++)
		cout << source[i] << endl;
}


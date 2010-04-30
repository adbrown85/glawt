/*
 * Program.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Program.hpp"
Program *Program::current=NULL;


/**
 * Creates a new %Program from an XML tag.
 * 
 * @param tag XML tag.
 */
Program::Program(const Tag& tag) : Applicable("Program") {
	
	handle = 0;
}


void Program::addCode(int handle,
                      const Preprocessor* preprocessor) {
	
	code[0] = preprocessor;
}


/**
 * Installs the program into the current context.
 */
void Program::apply() {
	
	glUseProgram(handle);
	current = this;
}


/**
 * Creates the program so other nodes can use it.
 */
void Program::associate() {
	
	// Create program
	handle = glCreateProgram();
}


/**
 * Links the program once other nodes have associated with it.
 * 
 * @throw const_char* if the program cannot be linked.
 */
void Program::finalize() {
	
	GLint linked=0;
	
	// Link
	glLinkProgram(handle);
	
	// Use if successful
	glGetProgramiv(handle, GL_LINK_STATUS, &linked);
	log();
	if (linked) {
		glUseProgram(handle);
	} else {
		throw "[Program] Could not link the shader program.";
	}
}


Program* Program::find(Node* node) {
	
	Program *program;
	
	// Look for a Program ancestor
	while (node != NULL) {
		program = dynamic_cast<Program*>(node);
		if (program != NULL)
			break;
		node = node->getParent();
	}
	return program;
}


/**
 * Prints the log for this program.
 */
void Program::log() const {
	
	GLchar *log;
	GLint count=0, returned=0;
	
	// Get length
	glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &count);
	
	// Print the log
	log = new GLchar[count+1];
	glGetProgramInfoLog(handle, count, &returned, log);
	log[returned] = '\0';
	Log::print(log, code);
	
	// Finish
	delete[] log;
}


/**
 * Stops using the program.
 */
void Program::remove() {
	
	// Restore fixed functionality
	glUseProgram(0);
	current = NULL;
}


/**
 * Forms a string from the object's attributes.
 */
string Program::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << " handle='" << handle << "'";
	return stream.str();
}


/*
 * Program.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Program.hpp"
Program *Program::current=NULL;



/**
 * Initializes the program's attributes.
 */
Program::Program() {
	
	// Initialize
	className = "Program";
	handle = 0;
}



/**
 * Creates a new %Program from an XML tag.
 * 
 * @param tag
 *     XML tag.
 */
Program::Program(const Tag &tag) {
	
	// Initialize
	className = "Program";
	handle = 0;
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
 */
void Program::finalize() {
	
	GLint linked=0;
	
	// Link
	glLinkProgram(handle);
	
	// Use if successful
	glGetProgramiv(handle, GL_LINK_STATUS, &linked);
	if (linked)
		glUseProgram(handle);
	else {
		cerr << "Gander,Program: Could not link the shader program." << endl;
		cerr << "Gander,Program: Printing log..." << endl;
		log();
		exit(1);
	}
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
	if (strlen(log) != 0)
		cerr << log << endl;
	
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
	
	stringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << " handle='" << handle << "'";
	return stream.str();
}


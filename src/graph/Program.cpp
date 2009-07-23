/*
 * Program.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Program.hpp"



/**
 * Initializes the program's attributes.
 */
Program::Program() {
	
	// Initialize
	name = 0;
}



/**
 * Installs the program into the current context.
 */
void Program::apply() {
	
	glUseProgram(name);
}



/**
 * Creates the program so other nodes can use it.
 */
void Program::associate() {
	
	// Create program
	name = glCreateProgram();
}



/**
 * Links the program once other nodes have associated with it.
 */
void Program::finalize() {
	
	GLint linked=0;
	
	// Link
	glLinkProgram(name);
	
	// Use if successful
	glGetProgramiv(name, GL_LINK_STATUS, &linked);
	if (!linked) {
		cerr << "Program: Could not link the shader program.";
		exit(1);
	}
}



/**
 * Stops using the program.
 */
void Program::remove() {
	
	// Restore fixed functionality
	glUseProgram(0);
}

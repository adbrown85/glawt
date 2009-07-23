/*
 * Program.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Program.hpp"



/**
 * Creates a new shader program.
 */
Program::Program() {
	
	// Initialize
	name = 0;
}



/**
 * Adds a shader to the program.
 * 
 * @param shader
 *     Pointer to a %Shader object.
 */
void Program::add(Shader *shader) {
	
	// Add
	shaders.push_back(shader);
}



/**
 * Compiles all the shaders in the program.
 */
void Program::compile() {
	
	// Compile each shader
	for (int i=0; i<shaders.size(); ++i) {
		shaders[i]->compile();
		glAttachShader(name, shaders[i]->getName());
	}
}



/**
 * Compiles and links the program.
 */
void Program::install() {
	
	// Create the program
	name = glCreateProgram();
	
	// Compile and link
	compile();
	link();
}



/**
 * Links and uses the program.
 */
void Program::link() {
	
	GLint linked=0;
	
	// Link
	glLinkProgram(name);
	
	// Use if successful
	glGetProgramiv(name, GL_LINK_STATUS, &linked);
	if (linked)
		glUseProgram(name);
	else {
		cerr << "Program: Could not link the shader program.";
		exit(1);
	}
}


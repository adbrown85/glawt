/*
 * Program.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Program.hpp"
Program *Program::current=NULL;


/** Creates a new %Program from an XML tag. */
Program::Program(const Tag& tag) : Node(tag) {
	
	handle = 0;
	linked = 0;
}


/** Adds link to shader code so linkage errors can be parsed. */
void Program::addCode(int handle, const Preprocessor* preprocessor) {
	
	code[0] = preprocessor;
}


/** Adds a listener to the program. */
void Program::addListener(NodeListener *listener, int type) {
	
	notifier.addListener(listener, type);
}


/** Installs the program into the current context. */
void Program::apply() {
	
	glUseProgram(handle);
	current = this;
}


/** Creates the program and finds the previous program. */
void Program::associate() {
	
	if (handle != 0)
		return;
	
	handle = glCreateProgram();
	previous = Scout<Program>::locate(getParent());
}


/** Links the program once other nodes have associated with it.
 * 
 * @throw NodeException if the program cannot be linked.
 */
void Program::finalize() {
	
	if (linked != 0)
		return;
	
	// Notify
	notifier.fireEvent(NodeEvent(this, NodeEvent::FINALIZE));
	
	// Link
	glLinkProgram(handle);
	
	// Use if successful
	glGetProgramiv(handle, GL_LINK_STATUS, &linked);
	log();
	if (linked) {
		glUseProgram(handle);
	} else {
		NodeException e(tag);
		e << "[Program] Could not link the shader program.";
		throw e;
	}
}


/** Prints the log for this program. */
void Program::log() const {
	
	GLchar *log;
	GLint count=0, returned=0;
	
	// Get length
	glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &count);
	
	// Print the log
	log = new GLchar[count+1];
	glGetProgramInfoLog(handle, count, &returned, log);
	log[returned] = '\0';
	Error::print(log, code);
	
	// Finish
	delete[] log;
}


/** Stop using this program and restore the previous one. */
void Program::remove() {
	
	current = previous;
	if (previous == NULL) {
		glUseProgram(0);
	} else {
		glUseProgram(previous->getHandle());
	}
}


/** Forms a string from the object's attributes. */
string Program::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << " handle='" << handle << "'";
	return stream.str();
}


/*
 * ErrorChecker.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ErrorChecker.hpp"


/** Checks for an OpenGL error. */
void ErrorChecker::check(const string &location) {
	
	GLenum error;
	
	error = glGetError();
	while (error != GL_NO_ERROR) {
		report(error, location);
		error = glGetError();
	}
}


/** Clears all the error flags. */
void ErrorChecker::clear() {
	
	GLenum error;
	
	error = glGetError();
	while (error != GL_NO_ERROR) {
		error = glGetError();
	}
}


/** Print information about an error. */
void ErrorChecker::report(GLenum error, const string &location) {
	
	glog << "At '" << location << "':" << endl;
	
	switch (error) {
	case GL_INVALID_ENUM:
		glog << "Invalid enumeration." << endl;
		break;
	case GL_INVALID_VALUE:
		glog << "Invalid value." << endl;
		break;
	case GL_INVALID_OPERATION:
		glog << "Invalid operation." << endl;
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		glog << "Invalid framebuffer operation." << endl;
		break;
	case GL_OUT_OF_MEMORY:
		glog << "Out of memory." << endl;
		break;
	default:
		throw new Exception("[ErrorChecker] Unexpected error flag.");
	}
}


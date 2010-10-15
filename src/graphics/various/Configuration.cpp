/*
 * Configuration.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Configuration.hpp"


int Configuration::getInteger(GLenum flag) {
	
	int value;
	
	glGetIntegerv(flag, &value);
	return value;
}


string Configuration::getString(GLenum flag) {
	
	const GLubyte *value;
	
	value = glGetString(flag);
	return string((char*)value);
}


int Configuration::getMaxColorAttachments() {
	
	return getInteger(GL_MAX_COLOR_ATTACHMENTS);
}


int Configuration::getMaxDrawBuffers() {
	
	return getInteger(GL_MAX_DRAW_BUFFERS);
}


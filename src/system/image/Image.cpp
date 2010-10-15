/*
 * Image.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Image.hpp"


/** Initialize filename. */
Image::Image(const string &filename) {
	
	this->filename = filename;
	this->width = 0;
	this->height = 0;
	this->format = GL_RGB;
}


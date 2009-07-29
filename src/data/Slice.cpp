/*
 * Slice.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Slice.hpp"



/**
 * Creates a new 
 * 
 * @param dataset
 *     Pointer to the volume data.
 * @param index
 *     Index into the %Dataset.
 */
Slice::Slice(Dataset *dataset,
             int index) {
	
	// Basics
	this->dataset = dataset;
	this->index = index;
	this->type = dataset->getTypeEnum();
	
	// Dimensions
	total = dataset->getDepth();
	width = dataset->getWidth();
	height = dataset->getHeight();
	length = width * height;
}



/**
 * Draws a slice to the screen.
 */
void Slice::draw() {
	
	int offset;
	
	// Calculate position for slice
	offset = index * length;
	
	// Draw pixels according to type
	switch (type) {
		case GL_FLOAT :
			drawAsFloat(offset);
			break;
		case GL_SHORT :
			drawAsShort(offset);
			break;
		case GL_UNSIGNED_BYTE : 
			drawAsUByte(offset);
			break;
		case GL_UNSIGNED_SHORT : 
			drawAsUShort(offset);
			break;
	}
}



/**
 * Draws the pixels as 32-bit, floating-point numbers.
 */
void Slice::drawAsFloat(int offset) {
	
	float *data;
	
	// Get data and draw 
	data = dataset->getFloatData() + offset;
	glDrawPixels(width, height, GL_LUMINANCE, GL_FLOAT, data);
}



/**
 * Draws the pixels as signed, 16-bit integers.
 */
void Slice::drawAsShort(int offset) {
	
	short *data;
	
	// Get data and draw 
	data = dataset->getShortData() + offset;
	glDrawPixels(width, height, GL_LUMINANCE, GL_SHORT, data);
}



/**
 * Draws the pixels as unsigned, 8-bit integers.
 */
void Slice::drawAsUByte(int offset) {
	
	unsigned char *data;
	
	// Get data and draw
	data = dataset->getUByteData() + offset;
	glDrawPixels(width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
}



/**
 * Draws the slice as unsigned, 16-bit integers.
 */
void Slice::drawAsUShort(int offset) {
	
	unsigned short *data;
	
	// Draw data
	data = dataset->getUShortData() + offset;
	glDrawPixels(width, height, GL_LUMINANCE, GL_UNSIGNED_SHORT, data);
}



/**
 * Updates the slice as the next one in the %Dataset.
 */
void Slice::next() {
	
	// Update index
	if (index == total-1)
		index = -1;
	++index;
}



/**
 * Updates the slice as the previous one in the %Dataset.
 */
void Slice::previous() {
	
	// Update index
	if (index == 0)
		index = total;
	--index;
}

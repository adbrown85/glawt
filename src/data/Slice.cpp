/*
 * Slice.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Slice.hpp"



/**
 * Creates a new %Slice.
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
	this->type = dataset->getType();
	
	// Dimensions
	total = dataset->getDepth();
	width = dataset->getWidth();
	height = dataset->getHeight();
	
	// Memory sizes
	length = width * height;
	block = dataset->getBlock();
}



/**
 * Draws a slice to the screen.
 */
void Slice::draw() {
	
	char *data;
	
	// Calculate position for slice
	data = reinterpret_cast<char*>(dataset->getData());
	data += index * length * block;
	glDrawPixels(width, height, GL_LUMINANCE, type, data);
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


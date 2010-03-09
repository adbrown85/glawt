/*
 * Dataset.cpp
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Dataset.hpp"


/**
 * Creates a new %Dataset from a file.
 * 
 * @param [in] filename
 *     Path to the file containing the data.
 */
Dataset::Dataset(string filename) :
                 header(filename) {
	
	// Initialize
	Dataset::init();
}


/**
 * Creates a new %Dataset from an XML tag.
 * 
 * @param [in] tag
 *     XML tag specifying the file with the data.
 */
Dataset::Dataset(const Tag &tag) :
                 header(tag) {
	
	// Initialize
	Dataset::init();
}


/**
 * Deallocates the data.
 */
Dataset::~Dataset() {
	
	free(data);
}


/**
 * Makes sure that an index is in bounds.
 * 
 * @param [in] index
 *     Integer coordinates specifying the location in the dataset.
 */
void Dataset::checkIndex(const Index &index) const {
	
	// Validate
	if (index.i < 0 || index.i > height
	    || index.j < 0 || index.j > width
	    || index.k < 0 || index.k > depth)
		throw "[Dataset] Index is out of bounds.";
}


/**
 * Finds a position in the array.
 * 
 * @param [in] index
 *     Integer coordinates specifying the location in the dataset.
 */
char* Dataset::findPosition(const Index &index) const {
	
	int offset;
	
	// Find position
	checkIndex(index);
	offset = (index.k * widthTimesHeight) + (index.i * width) + index.j;
	return (char*)(data) + (offset * block);
}


/**
 * Gets the value of an element in the data.
 * 
 * To dereference the pointer properly, use getType().
 * 
 * @param [in] index
 *     Integer coordinates specifying the location in the dataset.
 * @param [out] value
 *     Pointer to the value that will be set.
 * 
 * @note We don't make this method public because it has the potential to 
 * change the data.  (Even though it is declared @e const.)
 */
void Dataset::get(const Index &index,
                  void *&value) const {
	
	// Get value
	value = (void*)findPosition(index);
}


/**
 * Gets the value of an element in the data.
 * 
 * @param [in] I
 *     Integer coordinates specifying the location in the dataset.
 * @return Copy of the value as an unsigned byte.
 * 
 * @throws const_char* if the dataset's type is not GL_UNSIGNED_BYTE.
 * 
 * @note Remember if you want to print the value, cast it to an @c int first.
 */
unsigned char Dataset::getAsByte(const Index &I) const {
	
	void *value;
	
	// Check type
	if (type != GL_UNSIGNED_BYTE) {
		throw "[Dataset] Data is not made up of unsigned bytes.";
	}
	
	// Return the value
	get(I, value);
	return *((unsigned char*)value);
}


/**
 * Gets the value of an element in the data.
 * 
 * @param [in] I
 *     Integer coordinates specifying the location in the dataset.
 * @return Copy of the value as a float.
 * 
 * @throws const_char* if the dataset's type is not GL_FLOAT.
 */
float Dataset::getAsFloat(const Index &I) const {
	
	void *value;
	
	// Check type
	if (type != GL_FLOAT) {
		throw "[Dataset] Data is not made up of floats.";
	}
	
	// Return the value
	get(I, value);
	return *((float*)value);
}


/**
 * Gets the value of an element in the data.
 * 
 * @param [in] I
 *     Integer coordinates specifying the location in the dataset.
 * @return Copy of the value as a short.
 * 
 * @throws const_char* if the dataset's type is not GL_SHORT.
 */
short Dataset::getAsShort(const Index &I) const {
	
	void *value;
	
	// Check type
	if (type != GL_SHORT) {
		throw "[Dataset] Data is not made up of shorts.";
	}
	
	// Return the value
	get(I, value);
	return *((short*)value);
}


/**
 * @return the maximum of @c width, @c height, and @c depth.
 * 
 * @see getWidth()
 * @see getHeight()
 * @see getDepth()
 */
int Dataset::getMaximumDimension() const {
	
	int max;
	
	// Find max
	max = width;
	if (height > max)
		max = height;
	if (depth > max)
		max = depth;
	return max;
}


/**
 * Initializes attributes common to all constructors.
 */
void Dataset::init() {
	
	// Initialize
	initTypeBlock();
	initDimensions();
	
	// Allocate and read data
	data = malloc(length * block);
	readData();
}


/**
 * Initializes the dimensions of the dataset from its header.
 * 
 * @see getWidth()
 * @see getHeight()
 * @see getDepth()
 */
void Dataset::initDimensions() {
	
	// Dimensions of the dataset
	width = header.getWidth();
	height = header.getHeight();
	depth = header.getDepth();
	widthTimesHeight = width * height;
	
	// Length of the array to hold the dataset
	length = width * height * depth;
}


/**
 * Initializes the %Dataset's type and block based on the header.
 * 
 * @see getType()
 * @see getBlock()
 */
void Dataset::initTypeBlock() {
	
	string type=header.getType();
	
	// Set the type based on the header's type
	if (type.compare("uint8") == 0) {
		this->type = GL_UNSIGNED_BYTE;
		block = 1;
	}
	else if (type.compare("int16") == 0) {
		this->type = GL_SHORT;
		block = 2;
	}
	else if (type.compare("float") == 0) {
		this->type = GL_FLOAT;
		block = 4;
	}
	else
		throw "Gander,Dataset: Data type not currently supported.";
}


/**
 * Prints a value in the dataset.
 * 
 * @param [in] index
 *     Integer coordinates specifying the location in the dataset.
 */
void Dataset::print(Index index) {
	
	GLenum type;
	void *value;
	
	// Message
	cout << "Element at " << index << ":" << endl;
	
	// Get and print
	get(index, value, type);
	switch (type) {
		case GL_UNSIGNED_BYTE:
			cout << "  " << (int)*((unsigned char*)value) << endl;
			break;
		case GL_SHORT:
			cout << "  " << *((short*)value) << endl;
			break;
		case GL_FLOAT:
			cout << "  " << *((float*)value) << endl;
			break;
	}
}


/**
 * Reads the data from the file into the data array.
 */
void Dataset::readData() {
	
	ifstream file;
	string line;
	
	// Open the file
	file.open(header.getFilename().c_str(), ios_base::binary);
	if (!file)
		throw "Gander,Dataset: Could not open file in binary mode.";
	
	// Skip everything up to the data
	for (int i=0; i<header.getOffset(); ++i)
		getline(file, line);
	
	// Read the data by type
	file.read(reinterpret_cast<char*>(data), length * block);
	if (file.gcount() != length * block)
		throw "[Dataset] Did not read correct number of bytes.";
}


/**
 * Sets a sample in the dataset.
 * 
 * @param [in] index
 *     Index specifying the location of the sample.
 * @param [in] value
 *     Pointer to the value that the sample will be set to.
 * @param [in] type
 *     Type of the value to set.
 * 
 * @throws const_char* if the type passed does not match.
 * @see getType()
 */
void Dataset::set(const Index &index,
                  const void *value,
                  GLenum type) {
	
	void *position;
	
	// Check type
	if (type != this->type)
		throw "Gander,Dataset: Types do not match!";
	
	// Copy the value
	position = findPosition(index);
	memcpy(position, value, block);
}


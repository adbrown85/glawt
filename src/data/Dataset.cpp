/*
 * Dataset.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Dataset.hpp"
DatasetViewer *DatasetViewer::instance=NULL;


/** Creates a new %Dataset from a file.
 * 
 * @param [in] filename Path to the file containing the data.
 */
Dataset::Dataset(string filename) :
                 header(filename) {
	
	initTypeBlock();
	initDimensions();
}


/** Creates a new %Dataset from an XML tag.
 * 
 * @param [in] tag XML tag specifying the file with the data.
 */
Dataset::Dataset(const Tag &tag) :
                 header(tag) {
	
	initTypeBlock();
	initDimensions();
}


/** Deallocates the data. */
Dataset::~Dataset() {
	
	free(data);
}


/** Makes sure that an index is in bounds.
 * 
 * @param [in] index Integer coordinates specifying the location in dataset.
 * @throws Exception if index is out of bounds
 */
void Dataset::checkIndex(const Index &index) const {
	
	// Validate
	if (index.i < 0 || index.i > height
	      || index.j < 0 || index.j > width
	      || index.k < 0 || index.k > depth) {
		throw Exception("[Dataset] Index is out of bounds.");
	}
}


/** Finds a position in the array.
 * 
 * @param [in] index Integer coordinates specifying the location in dataset.
 */
char* Dataset::findPointerTo(const Index &I) const {
	
	return (char*)(data) + ((widthTimesHeight*I.k)+(width*I.i)+I.j) * block;
}


/** Gets the value of an element in the data.
 * 
 * To dereference the pointer properly, use getType().
 * 
 * @param [in] index Integer coordinates specifying the location in dataset.
 * @param [out] value Pointer to the value that will be set.
 * @note We don't make this method public because it has the potential to 
 * change the data.  (Even though it is declared @e const.)
 */
void Dataset::get(const Index &index,
                  void *&value) const {
	
	// Get value
	value = (void*)findPointerTo(index);
}


/** Gets the value of an element in the data.
 * 
 * @param [in] I Integer coordinates specifying the location in dataset.
 * @throws Exception if the dataset's type is not GL_UNSIGNED_BYTE.
 * @return Copy of the value as an unsigned byte.
 * @note Remember if you want to print the value, cast it to an @c int first.
 */
unsigned char Dataset::getAsByte(const Index &I) const {
	
	void *value;
	
	// Check type
	if (type != GL_UNSIGNED_BYTE) {
		throw Exception("[Dataset] Data is not made up of unsigned bytes.");
	}
	
	// Return the value
	get(I, value);
	return *((unsigned char*)value);
}


/** Gets the value of an element in the data.
 * 
 * @param [in] I Integer coordinates specifying the location in dataset.
 * @throws Exception if the dataset's type is not GL_FLOAT.
 * @return Copy of the value as a float.
 */
float Dataset::getAsFloat(const Index &I) const {
	
	void *value;
	
	// Check type
	if (type != GL_FLOAT) {
		throw Exception("[Dataset] Data is not made up of floats.");
	}
	
	// Return the value
	get(I, value);
	return *((float*)value);
}


/** Gets the value of an element in the data.
 * 
 * @param [in] I Integer coordinates specifying the location in dataset.
 * @throws Exception if the dataset's type is not GL_SHORT.
 * @return Copy of the value as a short.
 */
short Dataset::getAsShort(const Index &I) const {
	
	void *value;
	
	// Check type
	if (type != GL_SHORT) {
		throw Exception("[Dataset] Data is not made up of shorts.");
	}
	
	// Return the value
	get(I, value);
	return *((short*)value);
}


/** Gets the value of an element in the data.
 * 
 * @param [in] I Integer coordinates specifying the location in dataset.
 * @throws Exception if the dataset's type is not GL_SHORT.
 * @return Copy of the value as a short.
 */
unsigned short Dataset::getAsUnsignedShort(const Index &I) const {
	
	void *value;
	
	// Check type
	if (type != GL_UNSIGNED_SHORT) {
		throw Exception("[Dataset] Data is not made up of unsigned shorts.");
	}
	
	// Return the value
	get(I, value);
	return *((unsigned short*)value);
}


/** @return the maximum of @c width, @c height, and @c depth.
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


/** Initializes the dimensions of the dataset from its header.
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


/** Initializes the %Dataset's type and block based on the header.
 * 
 * @see getType()
 * @see getBlock()
 */
void Dataset::initTypeBlock() {
	
	string type=header.getType();
	
	// Set the type based on the header's type
	if (type == "uint8") {
		this->type = GL_UNSIGNED_BYTE;
		block = 1;
	} else if (type == "int16") {
		this->type = GL_SHORT;
		block = 2;
	} else if (type == "uint16") {
		this->type = GL_UNSIGNED_SHORT;
		block = 2;
	} else if (type == "float") {
		this->type = GL_FLOAT;
		block = 4;
	} else {
		throw Exception("[Dataset] Data type not currently supported.");
	}
}


void Dataset::load(bool raw) {
	
	// Allocate and read data
	data = malloc(length * block);
	readData();
	if (!raw && (getHigh()!=getMax() || getLow()!=getMin())) {
		normalize();
	}
}


void Dataset::normalize() {
	
	clock_t beg, end;
	
	cerr << "[Dataset] Normalizing... ";
	beg = clock();
	switch (type) {
	case GL_UNSIGNED_SHORT:
		normalizeAsUnsignedShort();
		break;
	}
	end = clock();
	cerr << (((double)end-beg)/CLOCKS_PER_SEC) << "s" << endl;
}


void Dataset::normalizeAsUnsignedShort() {
	
	GLfloat value;
	GLushort *p, *end;
	float rangeInv;
	
	rangeInv = ((float)1) / (getHigh() - getLow());
	p = (GLushort*)data;
	end = ((GLushort*)data) + length;
	while (p < end) {
		if ((int)(*p) < getLow()) {
			(*p) = 0;
		} else if ((int)(*p) > getHigh()) {
			(*p) = 1;
		} else {
			value = (float)((int)(*p) - getLow()) * rangeInv;
			*p = (GLushort)((float)value * 65535);
		}
		p += 1;
	}
}


/** Prints a value in the dataset.
 * 
 * @param [in] index Integer coordinates specifying the location in dataset.
 */
void Dataset::print(Index index) {
	
	// Message
	cout << "Element at " << index << ":" << endl;
	
	// Get and print
	switch (type) {
		case GL_UNSIGNED_BYTE:
			cout << "  " << (int)getAsByte(index) << endl;
			break;
		case GL_SHORT:
			cout << "  " << getAsShort(index) << endl;
			break;
		case GL_UNSIGNED_SHORT:
			cout << "  " << getAsUnsignedShort(index) << endl;
			break;
		case GL_FLOAT:
			cout << "  " << getAsFloat(index) << endl;
			break;
	}
}


/** Reads the data from the file into the data array. */
void Dataset::readData() {
	
	ifstream file;
	string line;
	
	// Open the file
	file.open(header.getFilename().c_str(), ios_base::binary);
	if (!file) {
		throw Exception("[Dataset] Could not open file in binary mode.");
	}
	
	// Skip everything up to the data
	for (int i=0; i<header.getOffset(); ++i)
		getline(file, line);
	
	// Read the data by type
	file.read(reinterpret_cast<char*>(data), length * block);
	if (file.gcount() != length * block) {
		throw Exception("[Dataset] Did not read correct number of bytes.");
	}
}


/** Sets a sample in the dataset.
 * 
 * @param [in] index Index specifying the location of the sample.
 * @param [in] value Pointer to the value that the sample will be set to.
 * @param [in] type Type of the value to set.
 * @throws const_char* if the type passed does not match.
 * @see getType()
 */
void Dataset::set(const Index &index,
                  const void *value,
                  GLenum type) {
	
	void *pointer;
	
	// Check type
	if (type != this->type) {
		throw Exception("[Dataset] Types do not match!");
	}
	
	// Copy the value
	pointer = findPointerTo(index);
	memcpy(pointer, value, block);
}


/** Draws a slice to the screen. */
void DatasetViewer::draw() {
	
	ostringstream stream;
	char *data;
	
	// Slice index
	stream << slice;
	Window::write(stream.str());
	
	// Reset raster position
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glRasterPos2f(-1.0, -1.0);
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	// Draw pixels
	data = reinterpret_cast<char*>(dataset->getData());
	data += slice * width * height * dataset->getBlock();
	glDrawPixels(width, height, GL_LUMINANCE, dataset->getType(), data);
}


/** Shows the next slice in the dataset. */
void DatasetViewer::goToNext() {
	
	if (slice == dataset->getDepth()-1)
		slice = -1;
	++slice;
	Window::refresh();
}


/** Shows the previous slice in the dataset. */
void DatasetViewer::goToPrevious() {
	
	if (slice == 0)
		slice = dataset->getDepth();
	--slice;
	Window::refresh();
}


/** Draws a slice to the screen. */
void DatasetViewer::onDisplay(void) {
	
	Window::clear();
	instance->draw();
	Window::flush();
}


/** Prints the value in the volume under the cursor. */
void DatasetViewer::onMouse(int button, int state, int x, int y) {
	
	// Ignore down state
	if (state == GLUT_DOWN) {
		return;
	}
	
	// Standard buttons
	if (button == GLUT_LEFT_BUTTON) {
		Index index(instance->height-y, x, instance->slice);
		switch (instance->type) {
		case GL_UNSIGNED_BYTE:
			cout << (int)instance->dataset->getAsByte(index) << endl;
			break;
		case GL_SHORT:
			cout << instance->dataset->getAsShort(index) << endl;
			break;
		case GL_UNSIGNED_SHORT:
			cout << instance->dataset->getAsUnsignedShort(index) << endl;
			break;
		case GL_FLOAT:
			cout << instance->dataset->getAsFloat(index) << endl;
			break;
		}
	}
	
	// Wheel
	else if (button == GLUT_UP_BUTTON) {
		instance->goToNext();
	} else if (button == GLUT_DOWN_BUTTON) {
		instance->goToPrevious();
	}
}


/** Changes the slice. */
void DatasetViewer::onSpecial(int key, int x, int y) {
	
	switch(key) {
	case GLUT_KEY_UP:
	case GLUT_KEY_RIGHT:
		instance->goToNext();
		break;
	case GLUT_KEY_DOWN:
	case GLUT_KEY_LEFT:
		instance->goToPrevious();
		break;
	}
}


void DatasetViewer::setDataset(Dataset *dataset) {
	
	this->dataset = dataset;
	this->width = dataset->getWidth();
	this->height = dataset->getHeight();
	this->depth = dataset->getDepth();
	this->type = dataset->getType();
	this->slice = 0;
}


/** Creates and runs the window. */
void DatasetViewer::start() {
	
	instance = this;
	
	// Create the window
	Window::create(dataset->getFilename(), width, height);
	
	// Set callbacks
	Window::setDisplay(&onDisplay);
	Window::setSpecial(&onSpecial);
	Window::setMouse(&onMouse);
	
	// Run
	Window::start();
}


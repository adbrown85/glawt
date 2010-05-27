/*
 * DatasetViewer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "DatasetViewer.hpp"
DatasetViewer *DatasetViewer::instance=NULL;


DatasetViewer::DatasetViewer() {
	
	instance = this;
}


/** Draws a slice to the screen. */
void DatasetViewer::draw() {
	
	ostringstream stream;
	char *data;
	
	// Slice index
	stream << slice;
	//Window::write(stream.str());
	
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
	canvas->refresh();
}


/** Shows the previous slice in the dataset. */
void DatasetViewer::goToPrevious() {
	
	if (slice == 0)
		slice = dataset->getDepth();
	--slice;
	canvas->refresh();
}


/** Draws a slice to the screen. */
void DatasetViewer::onDisplay(void) {
	
	instance->canvas->clear();
	instance->draw();
	instance->canvas->flush();
}


/** Prints the value in the volume under the cursor. */
void DatasetViewer::onMouse(int button, int state, int x, int y) {
	
	// Ignore down state
	if (state == CANVAS_DOWN) {
		return;
	}
	
	// Standard buttons
	if (button == CANVAS_LEFT_BUTTON) {
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
	else if (button == CANVAS_WHEEL_UP) {
		instance->goToNext();
	} else if (button == CANVAS_WHEEL_DOWN) {
		instance->goToPrevious();
	}
}


/** Changes the slice. */
void DatasetViewer::onSpecial(int key, int x, int y) {
	
	switch(key) {
	case CANVAS_KEY_UP:
	case CANVAS_KEY_RIGHT:
		instance->goToNext();
		break;
	case CANVAS_KEY_DOWN:
	case CANVAS_KEY_LEFT:
		instance->goToPrevious();
		break;
	}
}


void DatasetViewer::setDataset(Dataset *dataset) {
	
	// Set up fields
	this->dataset = dataset;
	this->width = dataset->getWidth();
	this->height = dataset->getHeight();
	this->depth = dataset->getDepth();
	this->type = dataset->getType();
	this->slice = 0;
	
	// Create the canvas
	canvas = new Canvas(width, height);
	canvas->setDisplayCallback(&onDisplay);
	canvas->setMouseCallback(&onMouse);
	canvas->setKeyboardCallback(&onSpecial);
	
	// Pack
	add(*canvas);
}


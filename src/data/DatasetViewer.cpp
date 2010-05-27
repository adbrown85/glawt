/*
 * DatasetViewer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "DatasetViewer.hpp"


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


/** Handles the incoming canvas event. */
void DatasetViewer::onCanvasEvent(const CanvasEvent &event) {
	
	switch (event.type) {
	case CanvasEvent::BUTTON :
		onCanvasEventButton(event);
		break;
	case CanvasEvent::DISPLAY :
		onCanvasEventDisplay(event);
		break;
	case CanvasEvent::KEY :
		onCanvasEventKey(event);
		break;
	}
}


/** Prints the value in the volume under the cursor. */
void DatasetViewer::onCanvasEventButton(const CanvasEvent &event) {
	
	// Ignore down state
	if (event.state.combo.action == CANVAS_DOWN) {
		return;
	}
	
	// Standard buttons
	if (event.state.combo.trigger == CANVAS_LEFT_BUTTON) {
		Index index((height-(event.state.y)), (event.state.x), slice);
		switch (type) {
		case GL_UNSIGNED_BYTE:
			cout << (int)(dataset->getAsByte(index)) << endl;
			break;
		case GL_SHORT:
			cout << dataset->getAsShort(index) << endl;
			break;
		case GL_UNSIGNED_SHORT:
			cout << dataset->getAsUnsignedShort(index) << endl;
			break;
		case GL_FLOAT:
			cout << dataset->getAsFloat(index) << endl;
			break;
		}
	}
	
	// Wheel
	else if (event.state.combo.trigger == CANVAS_WHEEL_UP) {
		goToNext();
	} else if (event.state.combo.trigger == CANVAS_WHEEL_DOWN) {
		goToPrevious();
	}
}


/** Draws a slice to the screen. */
void DatasetViewer::onCanvasEventDisplay(const CanvasEvent &event) {
	
	ostringstream stream;
	char *data;
	
	// Clear
	canvas->clear();
	
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
	
	// Flush
	canvas->flush();
}


/** Changes the slice. */
void DatasetViewer::onCanvasEventKey(const CanvasEvent &event) {
	
	switch(event.state.combo.trigger) {
	case CANVAS_KEY_UP:
	case CANVAS_KEY_RIGHT:
		goToNext();
		break;
	case CANVAS_KEY_DOWN:
	case CANVAS_KEY_LEFT:
		goToPrevious();
		break;
	}
}


void DatasetViewer::load() {
	
	// Set fields
	this->width = dataset->getWidth();
	this->height = dataset->getHeight();
	this->depth = dataset->getDepth();
	this->type = dataset->getType();
	this->slice = 0;
	
	// Create the canvas
	canvas->addListener(this, CanvasEvent::DISPLAY);
	canvas->addListener(this, CanvasEvent::BUTTON);
	canvas->addListener(this, CanvasEvent::KEY);
}


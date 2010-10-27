/*
 * Canvas.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Canvas.hpp"


/** Initializes the size of the widget. */
Canvas::Canvas(int width, int height) {
	
	this->width = width;
	this->height = height;
	this->automaticallyRefresh = false;
	this->isMouseButtonPressed = false;
	this->started = false;
}

/** Registers an object to receive updates from the canvas. */
void Canvas::addListener(CanvasListener *listener) {
	
	listeners.push_back(listener);
}

/** Notifies listeners of events. */
void Canvas::fireEvent(int type) {
	
	list<CanvasListener*>::iterator it;
	
	// Notify listeners
	for (it=listeners.begin(); it!=listeners.end(); ++it) {
		switch (type) {
		case CanvasEvent::INIT:
			(*it)->onCanvasInitEvent(*this);
			break;
		case CanvasEvent::DISPLAY:
			(*it)->onCanvasDisplayEvent(*this);
			break;
		case CanvasEvent::KEY:
			(*it)->onCanvasKeyEvent(*this);
			break;
		case CanvasEvent::BUTTON:
			(*it)->onCanvasButtonEvent(*this);
			break;
		case CanvasEvent::DRAG:
			(*it)->onCanvasDragEvent(*this);
			break;
		}
	}
}

/** Determines if events should be continuously sent to display listeners. */
void Canvas::setAutomaticallyRefresh(bool automaticallyRefresh) {
	
	this->automaticallyRefresh = automaticallyRefresh;
	if (started && automaticallyRefresh) {
		connectIdle();
	} else {
		disconnectIdle();
	}
}


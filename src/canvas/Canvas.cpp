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
void Canvas::addListener(CanvasListener *listener, int type) {
	
	// Check type
	if (type >= CANVAS_EVENT_TYPE_SIZE) {
		throw Exception("[Canvas] Illegal listener type specified.");
	}
	
	// Add it
	listeners[type].push_back(listener);
}


/** Wipes the canvas clean. */
void Canvas::clear() {
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}


/** Sends an event of the appropriate type. */
void Canvas::fireEvent(int type) {
	
	CanvasEvent event;
	list<CanvasListener*>::iterator it;
	
	// Make event
	event.type = type;
	event.source = this;
	event.state = state;
	
	// Send to listeners
	for (it=listeners[type].begin(); it!=listeners[type].end(); ++it) {
		(*it)->onCanvasEvent(event);
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


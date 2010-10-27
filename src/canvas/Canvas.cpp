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
	for (it=listeners.begin(); it!=listeners.end(); ++it) {
		switch (type) {
		case CanvasEvent::INIT:
			(*it)->onCanvasInitEvent(event);
			break;
		case CanvasEvent::DISPLAY:
			(*it)->onCanvasDisplayEvent(event);
			break;
		case CanvasEvent::KEY:
			(*it)->onCanvasKeyEvent(event);
			break;
		case CanvasEvent::BUTTON:
			(*it)->onCanvasButtonEvent(event);
			break;
		case CanvasEvent::DRAG:
			(*it)->onCanvasDragEvent(event);
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


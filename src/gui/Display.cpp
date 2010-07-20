/*
 * Display.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Display.hpp"


Display::Display(Delegate *delegate) {
	
	// Initialize attributes
	this->canvas = delegate->getCanvas();
	this->delegate = delegate;
	this->painter = new Painter(canvas, delegate->getScene());
	
	// Initialize overlay attributes
	this->useOverlay = false;
	this->timeStarted = 0;
	this->frames = 0;
	this->framesPerSecond = 0;
	computeFootprint();
	
	// Add listeners
	delegate->addListener(this, Command::INFORMATION);
	canvas->addListener(this, CanvasEvent::DISPLAY);
	
	// Get time
	timeMarker = canvas->getElapsedTime();
}


/** Installs a control into the display.
 * 
 * @param control Pointer to an object implementing the Control interface.
 */
void Display::add(Control *control) {
	
	list<Manipulator*> manips;
	list<Manipulator*>::iterator it;
	
	control->install();
	manips = control->getManipulators();
	for (it=manips.begin(); it!=manips.end(); ++it)
		painter->addManipulator(*it);
}


/** Adds up the footprints of all the textures in the scene. */
void Display::computeFootprint() {
	
	Scene *scene;
	list<Texture*> textures;
	list<Texture*>::iterator it;
	
	// Initialize
	scene = delegate->getScene();
	textures = Texture::search(scene->getRoot());
	
	// Accumulate
	footprint = 0;
	for (it=textures.begin(); it!=textures.end(); ++it) {
		footprint += (double)(*it)->getFootprint() / 1048576;
	}
}


/** Draws the scene in the window. */
void Display::onCanvasEvent(const CanvasEvent &event) {
	
	// Clear
	canvas->clear();
	
	// Paint scene and overlay
	painter->start();
	if (useOverlay)
		overlay();
	
	// Flush
	canvas->flush();
}


/** Handles command events. */
void Display::onCommandEvent(int command) {
	
	switch (command) {
	case Command::INFORMATION:
		toggleOverlay();
		break;
	}
}


/** Draws the overlay on the display. */
void Display::overlay() {
	
	GLuint time;
	ostringstream stream;
	
	// Update
	++frames;
	time = canvas->getElapsedTime();
	if (time - timeMarker > 1000) {
		framesPerSecond = frames;
		frames = 0;
		timeMarker = time;
	}
	
	// Draw text
	stream << "fps       " << framesPerSecond;
	canvas->write(stream.str(), 15, 50);
	stream.str("");
	stream << fixed << setprecision(2);
	stream << "footprint " << footprint << " MB";
	canvas->write(stream.str(), 15, 100);
}


/** Switches the overlay on and off. */
void Display::toggleOverlay() {
	
	useOverlay = !useOverlay;
	canvas->setAutomaticallyRefresh(useOverlay);
}


/*
 * Display.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Display.hpp"
Display *Display::obj=NULL;


Display::Display(Delegate *delegate) {
	
	Display::obj = this;
	
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
	
	// Register functions
	delegate->addListener(this, Command::INFORMATION);
	canvas->setDisplayCallback(&Display::display);
}


/** Installs a control into the display.
 * 
 * @param control Pointer to an object implementing the Control interface.
 */
void Display::add(Control *control) {
	
	vector<Manipulator*> manipulators;
	
	control->install();
	manipulators = control->getManipulators();
	for (size_t j=0; j<manipulators.size(); j++)
		painter->addManipulator(manipulators[j]);
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
void Display::display(void) {
	
	// Clear
	obj->canvas->clear();
	
	// Paint scene and overlay
	obj->painter->start();
	if (obj->useOverlay)
		obj->overlay();
	
	// Flush
	obj->canvas->flush();
}


/** Refreshes the display. */
void Display::idle(void) {
	
	obj->canvas->refresh();
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
	
	int time;
	ostringstream stream;
	
	// Update values
/*
	++frames;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timeStarted > 1000) {
		framesPerSecond = frames;
		frames = 0;
		timeStarted = time;
	}
*/
	
	// Draw text
	//stream << "fps       " << framesPerSecond;
	//Window::write(stream.str(), 15, 30);
	stream.str("");
	stream << fixed << setprecision(2);
	stream << "footprint " << footprint << " MB";
	//Window::write(stream.str(), 15, 50);
}


/** Switches the overlay on and off. */
void Display::toggleOverlay() {
	
	obj->useOverlay = !obj->useOverlay;
	//if (obj->useOverlay)
		//obj->canvas->setIdle(&Display::idle);
	//else
		//obj->canvas->setIdle(NULL);
}


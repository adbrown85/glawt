/*
 * Display.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Display.hpp"
Display *Display::obj=NULL;


Display::Display(Interpreter *interpreter) {
	
	Display::obj = this;
	
	// Initialize attributes
	this->interpreter = interpreter;
	this->painter = new Painter(interpreter->getScene());
	
	// Initialize overlay attributes
	this->useOverlay = false;
	this->timeStarted = 0;
	this->frames = 0;
	this->framesPerSecond = 0;
	computeFootprint();
	
	// Register functions
	interpreter->addListener(Command::INFORMATION, &Display::toggleOverlay);
	Window::setDisplay(&Display::display);
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
	scene = interpreter->getScene();
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
	Window::clear();
	
	// Paint scene and overlay
	obj->painter->start();
	if (obj->useOverlay)
		obj->overlay();
	
	// Flush
	Window::flush();
}


/** Refreshes the display. */
void Display::idle(void) {
	
	Window::refresh();
}


/** Draws the overlay on the display. */
void Display::overlay() {
	
	int time;
	ostringstream stream;
	
	// Update values
	++frames;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timeStarted > 1000) {
		framesPerSecond = frames;
		frames = 0;
		timeStarted = time;
	}
	
	// Draw text
	stream << "fps       " << framesPerSecond;
	Window::write(stream.str(), 15, 30);
	stream.str("");
	stream << fixed << setprecision(2);
	stream << "footprint " << footprint << " MB";
	Window::write(stream.str(), 15, 50);
}


void Display::toggleOverlay(int command) {
	
	obj->useOverlay = !obj->useOverlay;
	if (obj->useOverlay)
		Window::setIdle(&Display::idle);
	else
		Window::setIdle(NULL);
}


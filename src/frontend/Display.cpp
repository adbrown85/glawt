/*
 * Display.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Display.hpp"
Display *Display::obj=NULL;


Display::Display(Scene *scene,
                 const string &title) :
                 interpreter(scene) {
	
	// Initialize window
	Window::create(title);
	
	// Initialize attributes
	this->scene = scene;
	this->painter = new Painter(scene);
	Display::obj = this;
	
	// Initialize overlay attributes
	this->useOverlay = false;
	this->timeStarted = 0;
	this->frames = 0;
	this->framesPerSecond = 0;
}


/**
 * Draws the scene in the window.
 */
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


/**
 * Refreshes the display.
 */
void Display::idle(void) {
	
	Window::refresh();
}


/**
 * Installs a control into the display.
 * 
 * @param control Pointer to an object implementing the Control interface.
 */
void Display::install(Control *control) {
	
	controls.push_back(control);
}


/**
 * Draws the overlay on the display.
 */
void Display::overlay() {
	
	char buffer[32];
	float x, y;
	int time, viewport[4];
	
	// Update values
	++frames;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timeStarted > 1000) {
		framesPerSecond = frames;
		frames = 0;
		timeStarted = time;
	}
	
	// Calculate position
	glGetIntegerv(GL_VIEWPORT, viewport);
	x = ((float)viewport[2] - 15) / viewport[2];
	y = ((float)viewport[3] - 30) / viewport[3];
	
	// Set position
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glRasterPos2f(-x, y);
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	// Draw text
	sprintf(buffer, "fps: %d", framesPerSecond);
	for (size_t i=0; i<strlen(buffer); ++i)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, buffer[i]);
}


/**
 * Starts the display.
 */
void Display::start() {
	
	vector<Manipulator*> manipulators;
	
	// Open and prepare scene
	interpreter.run(Command::OPEN, scene->getFilename());
	interpreter.addListener(Command::INFORMATION, &Display::toggleOverlay);
	
	// Register functions
	Window::setDisplay(&Display::display);
	for (size_t i=0; i<controls.size(); i++) {
		controls[i]->install();
		manipulators = controls[i]->getManipulators();
		for (size_t j=0; j<manipulators.size(); j++)
			painter->addManipulator(manipulators[j]);
	}
	
	// Start
	Window::start();
}


void Display::toggleOverlay() {
	
	obj->useOverlay = !obj->useOverlay;
	if (obj->useOverlay)
		Window::setIdle(&Display::idle);
	else
		Window::setIdle(NULL);
}


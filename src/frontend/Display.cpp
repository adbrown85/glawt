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
	
	// Register functions
	interpreter->addListener(Command::INFORMATION, &Display::toggleOverlay);
	Window::setDisplay(&Display::display);
}


/**
 * Installs a control into the display.
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


void Display::toggleOverlay() {
	
	obj->useOverlay = !obj->useOverlay;
	if (obj->useOverlay)
		Window::setIdle(&Display::idle);
	else
		Window::setIdle(NULL);
}


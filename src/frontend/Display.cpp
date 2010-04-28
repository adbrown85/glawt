/*
 * Display.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Display.hpp"
Display *Display::obj=NULL;


Display::Display(Scene *scene,
                 const string &title,
                 int argc,
                 char *argv[]) :
                 interpreter(scene) {
	
	// Initialize attributes
	this->scene = scene;
	this->useOverlay = false;
	this->timeStarted = 0;
	this->frames = 0;
	this->framesPerSecond = 0;
	this->painter = NULL;
	this->height = scene->getHeight();
	this->width = scene->getWidth();
	this->title = title;
	Display::obj = this;
	
	// Initialize window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(DEFAULT_WINDOW_X, DEFAULT_WINDOW_Y);
	glutInitWindowSize(width, height);
	glutCreateWindow(title.c_str());
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	// Initialize view
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, static_cast<float>(width)/height, 0.1, 50.0);
	painter = new Painter(scene);
}


void Display::checkError() {
	
	GLenum error;
	
	error = glGetError();
	if (error != GL_NO_ERROR) {
		cerr << gluErrorString(error) << endl;
	}
}


/**
 * Draws the scene in the window.
 */
void Display::display(void) {
	
	// Initialize
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Paint scene and overlay
	obj->painter->paint();
	if (obj->useOverlay)
		obj->overlay();
	
	// Refresh
	glutSwapBuffers();
}


/**
 * Refreshes the display.
 */
void Display::idle(void) {
	
	glutPostRedisplay();
}


/**
 * Installs a control into the display.
 * 
 * @param control Pointer to an object implementing the Control interface.
 */
void Display::install(Control *control) {
	
	// Add to vector
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
	glutDisplayFunc(Display::display);
	for (size_t i=0; i<controls.size(); i++) {
		controls[i]->install();
		manipulators = controls[i]->getManipulators();
		for (size_t j=0; j<manipulators.size(); j++)
			painter->addManipulator(manipulators[j]);
	}
	
	// Start
	glutMainLoop();
}


void Display::toggleOverlay() {
	
	obj->useOverlay = !obj->useOverlay;
	if (obj->useOverlay)
		glutIdleFunc(Display::idle);
	else
		glutIdleFunc(NULL);
}


/*
 * Display.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Display.hpp"
Display *Display::obj=NULL;


Display::Display(Scene *scene,
                 Interpreter *interpreter) {
	
	// Copy inputs
	this->interpreter = interpreter;
	this->scene = scene;
	
	// Initialize others
	this->useOverlay = false;
	this->timeStarted = 0;
	this->frames = 0;
	this->framesPerSecond = 0;
	this->painter = new Painter(scene);
	
	// Store this instance
	Display::obj = this;
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
 * 
 * @param argc Number of arguments.
 * @param argv Array of argument values.
 * @param title Text to be shown on the window's title bar.
 * @param scene Pointer to a Scene with items (needs to be constructed first).
 * @param interpreter Delegate that opens scene.
 */
void Display::start(int argc,
                    char *argv[],
                    const string &title) {
	
	int width, height, x=100, y=100;
	vector<Manipulator*> manipulators;
	
	// Copy
	height = scene->getHeight();
	width = scene->getWidth();
	
	// Initialize window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(x, y);
	glutInitWindowSize(width, height);
	glutCreateWindow(title.c_str());
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glDepthFunc(GL_ALWAYS);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Initialize view
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, static_cast<float>(width)/height, 0.1, 50.0);
	
	// Open and prepare scene
	try {
		scene->install(new RenderFactory());
		scene->install(new ShaderFactory());
		scene->install(new ShapeFactory());
		scene->install(new TextureFactory());
		scene->install(new TransformFactory());
		interpreter->run(Command::OPEN, scene->getFilename());
		interpreter->addListener(Command::INFORMATION, &Display::toggleOverlay);
		scene->prepare();
		scene->print();
	} catch (char const *e) {
		cerr << e << endl;
		exit(1);
	}
	
	// Register functions
	glutDisplayFunc(Display::display);
	for (size_t i=0; i<controls.size(); i++) {
		manipulators = controls[i]->install(scene);
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


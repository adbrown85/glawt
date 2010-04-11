/*
 * Display.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Display.hpp"
Delegate *Display::delegate=NULL;
unsigned long Display::timeStarted=0;
int Display::frames=0, Display::framesPerSecond=0;
Scene *Display::scene=NULL;
vector<Control*> Display::controls;
vector<Manipulator*> Display::manipulators;


/**
 * Draws the scene in the window.
 */
void Display::display(void) {
	
	// Initialize
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Paint scene and overlay
	Painter::paint(*scene, manipulators);
	overlay();
	
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
 * @param control
 *     Pointer to an object implementing the Control interface.
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
 * @param title Text to be shown on the window's title bar.
 * @param scene Pointer to a Scene with items.  Needs to be constructed first.
 * @param delegate Delegate that opens scene.
 */
void Display::start(int argc,
                    char *argv[],
                    std::string title,
                    Scene *scene,
                    Delegate *delegate) {
	
	int width, height, x=100, y=100;
	vector<Manipulator*> manipulators;
	
	// Copy
	height = scene->getHeight();
	width = scene->getWidth();
	Display::scene = scene;
	Display::delegate = delegate;
	
	// Initialize window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(x, y);
	glutInitWindowSize(width, height);
	glutCreateWindow(title.c_str());
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glDepthFunc(GL_ALWAYS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Initialize view
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, static_cast<float>(width)/height, 0.1, 50.0);
	
	// Open and prepare scene
	try {
		delegate->run(Command::OPEN, scene->getFilename());
		scene->prepare();
		scene->print();
	}
	catch (char const *e) {
		cerr << e << endl;
		exit(1);
	}
	
	// Register functions
	glutDisplayFunc(Display::display);
	glutVisibilityFunc(Display::visibility);
	for (size_t i=0; i<controls.size(); i++) {
		manipulators = controls[i]->install(scene);
		for (size_t j=0; j<manipulators.size(); j++)
			Display::manipulators.push_back(manipulators[j]);
	}
	
	// Start
	glutMainLoop();
}


void Display::visibility(int visible) {
	
	if (visible)
		glutIdleFunc(Display::idle);
	else
		glutIdleFunc(NULL);
}


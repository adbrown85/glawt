/*
 * Window.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Window.hpp"
int Window::width, Window::height;
Quaternion Window::rotation;
Vector Window::position(0.0,0.0,DEFAULT_ZOOM,1.0);


/** Applies the camera position and rotation to the OpenGL modelview matrix. */
void Window::applyView() {
	
	float rotationArray[16];
	
	// Reset
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Position
	glTranslatef(position.x, position.y, position.z);
	
	// Rotation
	rotation.getMatrix().toArray(rotationArray);
	glMultMatrixf(rotationArray);
}


/** Checks if there were any OpenGL errors. */
void Window::check() {
	
	GLenum error;
	
	error = glGetError();
	if (error != GL_NO_ERROR) {
		cerr << gluErrorString(error) << endl;
	}
}


/** Allocates resources for the window and initializes OpenGL. */
void Window::create(const string &title, int width, int height) {
	
	// Store
	Window::width = width;
	Window::height = height;
	
	// Create window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(DEFAULT_SCREEN_X, DEFAULT_SCREEN_Y);
	glutInitWindowSize(width, height);
	glutCreateWindow(title.c_str());
	
	// Load default callbacks
	setDisplay(&display);
	setKeyboard(&keyboard);
	setMouse(&mouse);
	setSpecial(&special);
	
	// Enable options
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	// Set up viewport
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, static_cast<float>(width)/height, 0.1, 50.0);
}


/** Default display callback. */
void Window::display(void) {
	
	// Clear
	Window::clear();
	
	// Draw
	Window::applyView();
	glBegin(GL_QUADS);
		glVertex2f(+0.5, +0.5);
		glVertex2f(-0.5, +0.5);
		glVertex2f(-0.5, -0.5);
		glVertex2f(+0.5, -0.5);
	glEnd();
	Window::write("Window");
	
	// Flush
	Window::flush();
}


/** Default callback for keyboard presses. */
void Window::keyboard(unsigned char key, int x, int y) {
	
	switch (toupper(key)) {
	case 'R':
		reset();
		break;
	case 27:
	case 'Q':
		quit();
	}
}


/** Default callback for mouse clicks. */
void Window::mouse(int button, int state, int x, int y) {
	
	cerr << "Clicked at (" << x << "," << y << ")." << endl;
}


/** Default callback for special key presses. */
void Window::special(int key, int x, int y) {
	
	switch(key) {
	case GLUT_KEY_UP:
		rotate(-DEFAULT_ROTATE_AMOUNT, Vector(1.0,0.0,0.0));
		break;
	case GLUT_KEY_RIGHT:
		rotate(+DEFAULT_ROTATE_AMOUNT, Vector(0.0,1.0,0.0));
		break;
	case GLUT_KEY_DOWN:
		rotate(+DEFAULT_ROTATE_AMOUNT, Vector(1.0,0.0,0.0));
		break;
	case GLUT_KEY_LEFT:
		rotate(-DEFAULT_ROTATE_AMOUNT, Vector(0.0,1.0,0.0));
		break;
	}
}


/** Resets the window's rotation and position. */
void Window::reset() {
	
	// Reset transformations
	position.set(0.0, 0.0, DEFAULT_ZOOM);
	rotation.set(0.0, Vector(0.0,1.0,0.0));
	refresh();
}


/** Rotates the camera by axis/angle. */
void Window::rotate(float angle, const Vector &axis) {
	
	rotation.rotate(angle, axis);
	refresh();
}


/** Moves the camera. */
void Window::translate(const Vector &move) {
	
	position += move;
	refresh();
}


/** Writes a message onto the screen. */
void Window::write(const string &text, int x, int y) {
	
	float xf, yf;
	int viewport[4];
	
	// Calculate position
	glGetIntegerv(GL_VIEWPORT, viewport);
	xf = ((float)viewport[2] - x) / viewport[2];
	yf = ((float)viewport[3] - y) / viewport[3];
	
	// Set position
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glRasterPos2f(-xf, yf);
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	// Draw text
	for (size_t i=0; i<text.length(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]);
}


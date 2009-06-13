/*
 * Controls.cpp
 *     Keyboard and mouse controls for a 3D display.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#include "Controls.hpp"
Scene *Controls::scene=NULL;
bool Controls::allowRotate=false;
Vector Controls::last;



/**
 * Rotates or translates the scene by dragging one of the mouse buttons.
 */
void Controls::drag(int x,
                    int y) {
	
	int modifiers;
	float xDif, yDif;
	
	// Rotate the scene
	if (allowRotate) {
		xDif = last.x - x;
		yDif = last.y - y;
		scene->rotation.add(-yDif, -xDif);
		last.set(x, y);
		glutPostRedisplay();
	}
}



/**
 * Installs the controls into the current context.
 */
void Controls::install(Scene *scene) {
	
	// Copy
	Controls::scene = scene;
	
	// Register functions
	glutMotionFunc(Controls::drag);
	glutMouseFunc(Controls::mouse);
	glutSpecialFunc(Controls::special);
}



/**
 * Performs actions based on the button pressed.
 */
void Controls::mouse(int button,
                     int state,
                     int x,
                     int y) {
	
	// Pass on to button-specific function
	switch (button) {
		case GLUT_LEFT_BUTTON :
			std::cout << "Left mouse button!" << std::endl;
			rotate(state, x, y);
			break;
		case GLUT_RIGHT_BUTTON :
			std::cout << "Right mouse button!" << std::endl;
			break;
		default :
			break;
	}
}



/**
 * Handles keys with characters associated with them.
 */
/*
void keyboard() {
	
	
}
*/



/**
 * Enables or disables rotating the scene freely with the mouse.
 */
void Controls::rotate(int state,
                      int x,
                      int y) {
	
	int modifiers;
	
	// Set starting mouse position for rotating
	if (state == GLUT_DOWN) {
		modifiers = glutGetModifiers();
		if (modifiers == GLUT_ACTIVE_ALT) {
			allowRotate = true;
			last.set(x, y);
		}
	}
	else if (state == GLUT_UP) {
		allowRotate = false;
	}
}



/**
 * Handles special keys.
 */
void Controls::special(int key,
                       int x,
                       int y) {
	
	// 
	switch (key) {
		case GLUT_KEY_LEFT :
			scene->rotation.y -= CONTROLS_ROTATE_SPEED;
			break;
		case GLUT_KEY_RIGHT :
			scene->rotation.y += CONTROLS_ROTATE_SPEED;
			break;
		case GLUT_KEY_DOWN :
			scene->rotation.x += CONTROLS_ROTATE_SPEED;
			break;
		case GLUT_KEY_UP :
			scene->rotation.x -= CONTROLS_ROTATE_SPEED;
			break;
		case GLUT_KEY_HOME :
			scene->reset();
			break;
	}
	glutPostRedisplay();
}

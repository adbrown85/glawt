/*
 * Mouse.cpp
 *     Mouse control for a 3D display.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Mouse.hpp"
Mouse *Mouse::instance=NULL;



/**
 * Installs the control into the current context.
 */
void Mouse::install() {
	
	// Register functions
	Mouse::instance = this;
	glutMouseFunc(Mouse::mouse);
	glutMotionFunc(Mouse::motion);
}



/**
 * Rotates or translates the scene by dragging one of the mouse buttons.
 */
void Mouse::motion(int x,
                   int y) {
	
	Delegate *del=Mouse::instance->del;
	int xDif, yDif;
	
	// Initialize
	xDif = Mouse::instance->xLast - x;
	yDif = Mouse::instance->yLast - y;
	
	// Rotate the scene
	if (Mouse::instance->allowRotate) {
		if (xDif < 0)
			del->run(Command::CIRCLE_RIGHT, xDif);
		else if (xDif > 0)
			del->run(Command::CIRCLE_LEFT, xDif);
		if (yDif < 0)
			del->run(Command::CIRCLE_DOWN, yDif);
		else if (yDif > 0)
			del->run(Command::CIRCLE_UP, yDif);
	}
	else if (Mouse::instance->allowTrans) {
		if (xDif < 0)
			del->run(Command::TRACK_RIGHT, xDif);
		else if (xDif > 0)
			del->run(Command::TRACK_LEFT, xDif);
		if (yDif < 0)
			del->run(Command::BOOM_DOWN, yDif);
		else if (yDif > 0)
			del->run(Command::BOOM_UP, yDif);
	}
	
	// Save for next time
	Mouse::instance->xLast = x;
	Mouse::instance->yLast = y;
	
	// Refresh
	glutPostRedisplay();
}



/**
 * Handles mouse clicks.
 */
void Mouse::mouse(int button,
                  int action,
                  int x,
                  int y) {
	
	Delegate *del=Mouse::instance->del;
	State *state=Mouse::instance->state;
	
	// Run command
	switch (button) {
		case GLUT_MIDDLE_BUTTON :
			if (action == GLUT_DOWN)
				Mouse::instance->allowTrans = true;
			else
				Mouse::instance->allowTrans = false;
			break;
		case GLUT_LEFT_BUTTON :
			if (action == GLUT_DOWN) {
				if (glutGetModifiers() != GLUT_ACTIVE_ALT)
					Mouse::instance->allowRotate = true;
			}
			else {
				Mouse::instance->allowRotate = false;
				if (glutGetModifiers() == GLUT_ACTIVE_ALT) {
					del->run(Command::GRAB, x, y);
					glutPostRedisplay();
				}
			}
			break;
		case GLUT_WHEEL_DOWN :
			if (action == GLUT_DOWN)
				del->run(Command::ZOOM_OUT, 1.0);
				glutPostRedisplay();
			break;
		case GLUT_WHEEL_UP :
			if (action == GLUT_DOWN)
				del->run(Command::ZOOM_IN, 1.0);
				glutPostRedisplay();
			break;
		default :
			break;
	}
	
	// Save for next time
	Mouse::instance->xLast = x;
	Mouse::instance->yLast = y;
}

/*
 * Cameraman.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Cameraman.hpp"


/**
 * Adds the commands this delegate supports and sets up handlers.
 */
Cameraman::Cameraman() {
	
	// Set type
	type = "Cameraman";
	
	// Add zero-argument handlers
	handlersZero[Command::FIT_SELECTED] = &Cameraman::fit;
	handlersZero[Command::FIT_ALL] = &Cameraman::fit;
	handlersZero[Command::RESET] = &Cameraman::reset;
	
	// Add one-argument handlers
	handlersFloat[Command::BOOM] = &Cameraman::translate;
	handlersFloat[Command::BOOM_DOWN] = &Cameraman::translate;
	handlersFloat[Command::BOOM_UP] = &Cameraman::translate;
	handlersFloat[Command::CIRCLE_X] = &Cameraman::rotate;
	handlersFloat[Command::CIRCLE_Y] = &Cameraman::rotate;
	handlersFloat[Command::CIRCLE_LEFT] = &Cameraman::rotate;
	handlersFloat[Command::CIRCLE_RIGHT] = &Cameraman::rotate;
	handlersFloat[Command::CIRCLE_DOWN] = &Cameraman::rotate;
	handlersFloat[Command::CIRCLE_UP] = &Cameraman::rotate;
	handlersFloat[Command::ZOOM_IN] = &Cameraman::translate;
	handlersFloat[Command::ZOOM_OUT] = &Cameraman::translate;
	handlersFloat[Command::TRACK] = &Cameraman::translate;
	handlersFloat[Command::TRACK_LEFT] = &Cameraman::translate;
	handlersFloat[Command::TRACK_RIGHT] = &Cameraman::translate;
}


/**
 * Fits items in the view.
 */
void Cameraman::fit(Scene *scene,
                    int cmd) {
	
	cout << "Cameraman::fit(int)" << endl;
}


/**
 * Resets the view's rotation.
 */
void Cameraman::reset(Scene *scene,
                      int cmd) {
	
	Window::reset();
}


/**
 * Rotates the camera around the scene.
 * 
 * @param scene Pointer to the current scene.
 * @param cmd Command (should be in CIRCLE family).
 * @param amt Amount to rotate the camera.
 */
void Cameraman::rotate(Scene *scene,
                       int cmd,
                       float amt) {
	
	// Rotate according to command
	switch (cmd) {
	case Command::CIRCLE_X :
		Window::rotate( amt, Vector(1.0,0.0,0.0)); break;
	case Command::CIRCLE_Y :
		Window::rotate(-amt, Vector(0.0,1.0,0.0)); break;
	case Command::CIRCLE_LEFT :
		Window::rotate(-fabs(amt), Vector(0.0,1.0,0.0)); break;
	case Command::CIRCLE_RIGHT :
		Window::rotate( fabs(amt), Vector(0.0,1.0,0.0)); break;
	case Command::CIRCLE_UP :
		Window::rotate(-fabs(amt), Vector(1.0,0.0,0.0)); break;
	case Command::CIRCLE_DOWN :
		Window::rotate( fabs(amt), Vector(1.0,0.0,0.0)); break;
	}
}


/**
 * Moves the camera.
 * 
 * @param scene Pointer to the current scene.
 * @param cmd Command (either BOOM, TRACK, or ZOOM family).
 * @param amt Amount to move the camera.
 */
void Cameraman::translate(Scene *scene,
                          int cmd,
                          float amt) {
	
	switch (cmd) {
	case Command::BOOM :
		Window::translate(0.0,       amt *0.011, 0.0);
		break;
	case Command::BOOM_DOWN :
		Window::translate(0.0, -fabs(amt)*0.011, 0.0);
		break;
	case Command::BOOM_UP :
		Window::translate(0.0, +fabs(amt)*0.011, 0.0);
		break;
	case Command::TRACK :
		Window::translate(     -amt *0.011, 0.0, 0.0);
		break;
	case Command::TRACK_LEFT :
		Window::translate(+fabs(amt)*0.011, 0.0, 0.0);
		break;
	case Command::TRACK_RIGHT :
		Window::translate(-fabs(amt)*0.011, 0.0, 0.0);
		break;
	case Command::ZOOM_IN :
		Window::translate(0.0, 0.0, +amt);
		break;
	case Command::ZOOM_OUT :
		Window::translate(0.0, 0.0, -amt);
		break;
	}
}


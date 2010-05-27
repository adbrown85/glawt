/*
 * Cameraman.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Cameraman.hpp"


/** Stores the inputs */
Cameraman::Cameraman(Scene *scene, Canvas *canvas) {
	
	this->scene = scene;
	this->canvas = canvas;
}


/** Fits items in the view. */
void Cameraman::fit(int cmd) {
	
	cout << "Cameraman::fit(int)" << endl;
}


/** Resets the view's rotation. */
void Cameraman::reset(int cmd) {
	
	canvas->reset();
}


/** Rotates the camera around the scene.
 * 
 * @param cmd Command (should be in CIRCLE family).
 * @param amt Amount to rotate the camera.
 */
void Cameraman::rotate(int cmd, float amt) {
	
	// Rotate according to command
	switch (cmd) {
	case Command::CIRCLE_X :
		canvas->rotate( amt, Vector(1.0,0.0,0.0)); break;
	case Command::CIRCLE_Y :
		canvas->rotate(-amt, Vector(0.0,1.0,0.0)); break;
	case Command::CIRCLE_LEFT :
		canvas->rotate(-fabs(amt), Vector(0.0,1.0,0.0)); break;
	case Command::CIRCLE_RIGHT :
		canvas->rotate( fabs(amt), Vector(0.0,1.0,0.0)); break;
	case Command::CIRCLE_UP :
		canvas->rotate(-fabs(amt), Vector(1.0,0.0,0.0)); break;
	case Command::CIRCLE_DOWN :
		canvas->rotate( fabs(amt), Vector(1.0,0.0,0.0)); break;
	}
}


/** Moves the camera.
 * 
 * @param cmd Command (either BOOM, TRACK, or ZOOM family).
 * @param amt Amount to move the camera.
 */
void Cameraman::translate(int cmd, float amt) {
	
	switch (cmd) {
	case Command::BOOM :
		canvas->translate(0.0,       amt *0.011, 0.0);
		break;
	case Command::BOOM_DOWN :
		canvas->translate(0.0, -fabs(amt)*0.011, 0.0);
		break;
	case Command::BOOM_UP :
		canvas->translate(0.0, +fabs(amt)*0.011, 0.0);
		break;
	case Command::TRACK :
		canvas->translate(     -amt *0.011, 0.0, 0.0);
		break;
	case Command::TRACK_LEFT :
		canvas->translate(+fabs(amt)*0.011, 0.0, 0.0);
		break;
	case Command::TRACK_RIGHT :
		canvas->translate(-fabs(amt)*0.011, 0.0, 0.0);
		break;
	case Command::ZOOM_IN :
		canvas->translate(0.0, 0.0, +amt);
		break;
	case Command::ZOOM_OUT :
		canvas->translate(0.0, 0.0, -amt);
		break;
	}
}


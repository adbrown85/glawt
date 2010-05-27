/*
 * Cameraman.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Cameraman.hpp"


/** Fits items in the view. */
void Cameraman::fit(int cmd) {
	
	cout << "Cameraman::fit(int)" << endl;
}


/** Resets the view's rotation. */
void Cameraman::reset(int cmd) {
	
	canvas->getCamera()->reset();
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
		canvas->getCamera()->rotate( amt, Vector(1.0,0.0,0.0)); break;
	case Command::CIRCLE_Y :
		canvas->getCamera()->rotate(-amt, Vector(0.0,1.0,0.0)); break;
	case Command::CIRCLE_LEFT :
		canvas->getCamera()->rotate(-fabs(amt), Vector(0.0,1.0,0.0)); break;
	case Command::CIRCLE_RIGHT :
		canvas->getCamera()->rotate( fabs(amt), Vector(0.0,1.0,0.0)); break;
	case Command::CIRCLE_UP :
		canvas->getCamera()->rotate(-fabs(amt), Vector(1.0,0.0,0.0)); break;
	case Command::CIRCLE_DOWN :
		canvas->getCamera()->rotate( fabs(amt), Vector(1.0,0.0,0.0)); break;
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
		canvas->getCamera()->move(Vector(0.0,       amt *0.011, 0.0));
		break;
	case Command::BOOM_DOWN :
		canvas->getCamera()->move(Vector(0.0, -fabs(amt)*0.011, 0.0));
		break;
	case Command::BOOM_UP :
		canvas->getCamera()->move(Vector(0.0, +fabs(amt)*0.011, 0.0));
		break;
	case Command::TRACK :
		canvas->getCamera()->move(Vector(     -amt *0.011, 0.0, 0.0));
		break;
	case Command::TRACK_LEFT :
		canvas->getCamera()->move(Vector(+fabs(amt)*0.011, 0.0, 0.0));
		break;
	case Command::TRACK_RIGHT :
		canvas->getCamera()->move(Vector(-fabs(amt)*0.011, 0.0, 0.0));
		break;
	case Command::ZOOM_IN :
		canvas->getCamera()->move(Vector(0.0, 0.0, +amt));
		break;
	case Command::ZOOM_OUT :
		canvas->getCamera()->move(Vector(0.0, 0.0, -amt));
		break;
	}
}


/*
 * Cameraman.cpp
 *     Responsible for moving the camera.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
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
void Cameraman::fit(Scene *scene, int cmd) {
	
	std::cout << "Cameraman::fit(int)" << std::endl;
}



/**
 * Resets the view's rotation.
 */
void Cameraman::reset(Scene *scene, int cmd) {
	
	// Resets rotation
	scene->setRotation(0.0, 0.0, 1.0, 0.0);
	scene->position.set(0.0, 0.0, -10);
}



/**
 * Rotates the camera around the scene.
 * 
 * @param cmd
 *     Command.  Should be in CIRCLE family.
 * @param amt
 *     Amount to rotate the camera.
 */
void Cameraman::rotate(Scene *scene, int cmd, float amt) {
	
	// Rotate according to command
	switch (cmd) {
		case Command::CIRCLE_X :
			scene->rotate( amt, 1.0, 0.0, 0.0); break;
		case Command::CIRCLE_Y :
			scene->rotate(-amt, 0.0, 1.0, 0.0); break;
		case Command::CIRCLE_LEFT :
			scene->rotate(-fabs(amt), 0.0, 1.0, 0.0); break;
		case Command::CIRCLE_RIGHT :
			scene->rotate( fabs(amt), 0.0, 1.0, 0.0); break;
		case Command::CIRCLE_UP :
			scene->rotate(-fabs(amt), 1.0, 0.0, 0.0); break;
		case Command::CIRCLE_DOWN :
			scene->rotate( fabs(amt), 1.0, 0.0, 0.0); break;
	}
}



/**
 * Moves the camera.
 * 
 * @param cmd
 *     Command.  Either BOOM, TRACK, or ZOOM family.
 * @param amt
 *     Amount to move the camera.
 */
void Cameraman::translate(Scene *scene, int cmd, float amt) {
	
	switch (cmd) {
		case Command::BOOM :
			scene->position.y += amt * 0.011; break;
		case Command::BOOM_DOWN :
			scene->position.y -= fabs(amt) * 0.011; break;
		case Command::BOOM_UP :
			scene->position.y += fabs(amt) * 0.011; break;
		case Command::TRACK :
			scene->position.x -= amt * 0.011; break;
		case Command::TRACK_LEFT :
			scene->position.x += fabs(amt) * 0.011; break;
		case Command::TRACK_RIGHT :
			scene->position.x -= fabs(amt) * 0.011; break;
		case Command::ZOOM_IN :
			scene->position.z += amt; break;
		case Command::ZOOM_OUT :
			scene->position.z -= amt; break;
	}
}

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
	
	std::map<int,void(Cameraman::*)(int)>::iterator h0;
	std::map<int,void(Cameraman::*)(int,float)>::iterator h1;
	
	// Set type
	type = "Cameraman";
	
	// Add zero-argument handlers
	hans0[Command::FIT_SELECTED] = &Cameraman::cmdFit;
	hans0[Command::FIT_ALL] = &Cameraman::cmdFit;
	hans0[Command::RESET] = &Cameraman::cmdReset;
	
	// Add one-argument handlers
	hans1[Command::BOOM] = &Cameraman::cmdTrans;
	hans1[Command::BOOM_DOWN] = &Cameraman::cmdTrans;
	hans1[Command::BOOM_UP] = &Cameraman::cmdTrans;
	hans1[Command::CIRCLE_X] = &Cameraman::cmdRotate;
	hans1[Command::CIRCLE_Y] = &Cameraman::cmdRotate;
	hans1[Command::CIRCLE_LEFT] = &Cameraman::cmdRotate;
	hans1[Command::CIRCLE_RIGHT] = &Cameraman::cmdRotate;
	hans1[Command::CIRCLE_DOWN] = &Cameraman::cmdRotate;
	hans1[Command::CIRCLE_UP] = &Cameraman::cmdRotate;
	hans1[Command::ZOOM_IN] = &Cameraman::cmdTrans;
	hans1[Command::ZOOM_OUT] = &Cameraman::cmdTrans;
	hans1[Command::TRACK] = &Cameraman::cmdTrans;
	hans1[Command::TRACK_LEFT] = &Cameraman::cmdTrans;
	hans1[Command::TRACK_RIGHT] = &Cameraman::cmdTrans;
	
	// Publish commands
	for (h0=hans0.begin(); h0!=hans0.end(); h0++)
		cmds.push_back(h0->first);
	for (h1=hans1.begin(); h1!=hans1.end(); h1++)
		cmds.push_back(h1->first);
}



/**
 * Interprets a command.
 */
void Cameraman::run(int command) {
	
	void (Cameraman::*method)(int)=NULL;
	
	// Filter command to correct method
	method = hans0[command];
	if (method != NULL)
		(this->*method)(command);
}



/**
 * Interprets a command.
 */
void Cameraman::run(int command, float argument) {
	
	void (Cameraman::*method)(int,float)=NULL;
	
	// Filter command to correct method
	method = hans1[command];
	if (method != NULL)
		(this->*method)(command, argument);
}



/**
 * Fits items in the view.
 */
void Cameraman::cmdFit(int cmd) {
	
	std::cout << "Cameraman::cmdFit(int)" << std::endl;
}



/**
 * Resets the view.  Zeros it out, except for the zoom, which is based on 
 * scene size.
 */
void Cameraman::cmdReset(int cmd) {
	
	std::cout << "Cameraman::cmdReset(int)" << std::endl;
}



/**
 * Rotates the camera around the scene.
 * 
 * @param cmd
 *     Command.  Should be in CIRCLE family.
 * @param amt
 *     Amount to rotate the camera.
 */
void Cameraman::cmdRotate(int cmd, float amt) {
	
	// 
	switch (cmd) {
		case Command::CIRCLE_X : {
			scene->rotation.x += amt;
			break;
		}
		case Command::CIRCLE_Y :
			scene->rotation.y -= amt;
			break;
		case Command::CIRCLE_LEFT :
			amt = fabs(amt);
			scene->rotation.y -= amt;
			break;
		case Command::CIRCLE_RIGHT :
			amt = fabs(amt);
			scene->rotation.y += amt;
			break;
		case Command::CIRCLE_UP :
			amt = fabs(amt);
			scene->rotation.x -= amt;
			break;
		case Command::CIRCLE_DOWN :
			amt = fabs(amt);
			scene->rotation.x += amt;
			break;
	}
}



/**
 * Moves the camera.
 * 
 * @param cmd
 *     Command.  Either BOOM, TRACK, or ZOOM family.
 * @param amt
 *     Amount to move the camera.  Will alter based on scene size.
 */
void Cameraman::cmdTrans(int cmd, float amt) {
	
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

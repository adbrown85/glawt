/*
 * Grip.cpp
 *     Responsible for creating and storing scenes.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Grip.hpp"



/**
 * Adds the commands this delegate supports and sets up handlers.
 */
Grip::Grip() {
	
	std::map<int,void(Grip::*)(int)>::iterator h;
	
	// Set type
	type = "Grip";
	
	// Add handlers
	hans[Command::ROTATE_X_MINUS] = &Grip::cmdRotate;
	hans[Command::ROTATE_X_PLUS] = &Grip::cmdRotate;
	hans[Command::ROTATE_Y_MINUS] = &Grip::cmdRotate;
	hans[Command::ROTATE_Y_PLUS] = &Grip::cmdRotate;
	hans[Command::ROTATE_Z_MINUS] = &Grip::cmdRotate;
	hans[Command::ROTATE_Z_PLUS] = &Grip::cmdRotate;
	hans[Command::SCALE_X_MINUS] = &Grip::cmdScale;
	hans[Command::SCALE_X_PLUS] = &Grip::cmdScale;
	hans[Command::SCALE_Y_MINUS] = &Grip::cmdScale;
	hans[Command::SCALE_Y_PLUS] = &Grip::cmdScale;
	hans[Command::SCALE_Z_MINUS] = &Grip::cmdScale;
	hans[Command::SCALE_Z_PLUS] = &Grip::cmdScale;
	hans[Command::TRANSLATE_X_MINUS] = &Grip::cmdTranslate;
	hans[Command::TRANSLATE_X_PLUS] = &Grip::cmdTranslate;
	hans[Command::TRANSLATE_Y_MINUS] = &Grip::cmdTranslate;
	hans[Command::TRANSLATE_Y_PLUS] = &Grip::cmdTranslate;
	hans[Command::TRANSLATE_Z_MINUS] = &Grip::cmdTranslate;
	hans[Command::TRANSLATE_Z_PLUS] = &Grip::cmdTranslate;
	
	// Copy commands
	for (h=hans.begin(); h!=hans.end(); h++)
		cmds.push_back(h->first);
}



/**
 * Interprets a command.
 */
void Grip::run(int command) {
	
	void (Grip::*method)(int);
	
	// Filter command to correct method
	method = hans[command];
	(this->*method)(command);
}



/**
 * Rotates the current selection.
 */
void Grip::cmdRotate(int cmd) {
	
/*
	switch (cmd) {
		case Command::ROTATE_X_MINUS :
			scene->rotation.x -= 2.0; break;
		case Command::ROTATE_X_PLUS :
			scene->rotation.x += 2.0; break;
		case Command::ROTATE_Y_MINUS :
			scene->rotation.y -= 2.0; break;
		case Command::ROTATE_Y_PLUS :
			scene->rotation.y += 2.0; break;
		case Command::ROTATE_Z_MINUS :
			scene->rotation.z -= 2.0; break;
		case Command::ROTATE_Z_PLUS :
			scene->rotation.z += 2.0; break;
	}
*/
	glutPostRedisplay();
}



/**
 * Scales the current selection.
 */
void Grip::cmdScale(int cmd) {
	
	std::cout << "Grip::cmdScale(int)" << std::endl;
}



/**
 * Translates the current selection.
 */
void Grip::cmdTranslate(int cmd) {
	
	switch (cmd) {
		case Command::TRANSLATE_X_MINUS :
			scene->position.x -= 2.0; break;
		case Command::TRANSLATE_X_PLUS :
			scene->position.x += 2.0; break;
		case Command::TRANSLATE_Y_MINUS :
			scene->position.y -= 2.0; break;
		case Command::TRANSLATE_Y_PLUS :
			scene->position.y += 2.0; break;
		case Command::TRANSLATE_Z_MINUS :
			scene->position.z -= 2.0; break;
		case Command::TRANSLATE_Z_PLUS :
			scene->position.z += 2.0; break;
	}
	glutPostRedisplay();
}

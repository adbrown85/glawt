/*
 * Grip.cpp
 *     Responsible for creating and storing scenes.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Grip.hpp"



/**
 * Adds the handlers Grip supports.
 */
Grip::Grip() {
	
	// Set type
	type = "Grip";
	
	// Add handlers
	handlersZero[Command::ROTATE_X_MINUS] = &Grip::rotate;
	handlersZero[Command::ROTATE_X_PLUS] = &Grip::rotate;
	handlersZero[Command::ROTATE_Y_MINUS] = &Grip::rotate;
	handlersZero[Command::ROTATE_Y_PLUS] = &Grip::rotate;
	handlersZero[Command::ROTATE_Z_MINUS] = &Grip::rotate;
	handlersZero[Command::ROTATE_Z_PLUS] = &Grip::rotate;
	handlersZero[Command::SCALE_X_MINUS] = &Grip::scale;
	handlersZero[Command::SCALE_X_PLUS] = &Grip::scale;
	handlersZero[Command::SCALE_Y_MINUS] = &Grip::scale;
	handlersZero[Command::SCALE_Y_PLUS] = &Grip::scale;
	handlersZero[Command::SCALE_Z_MINUS] = &Grip::scale;
	handlersZero[Command::SCALE_Z_PLUS] = &Grip::scale;
	handlersZero[Command::TRANSLATE_X_MINUS] = &Grip::translate;
	handlersZero[Command::TRANSLATE_X_PLUS] = &Grip::translate;
	handlersZero[Command::TRANSLATE_Y_MINUS] = &Grip::translate;
	handlersZero[Command::TRANSLATE_Y_PLUS] = &Grip::translate;
	handlersZero[Command::TRANSLATE_Z_MINUS] = &Grip::translate;
	handlersZero[Command::TRANSLATE_Z_PLUS] = &Grip::translate;
}



/**
 * Rotates the current selection.
 */
void Grip::rotate(Scene *scene, int command) {
	
	std::cout << "Grip::rotate(Scene*,int)" << std::endl;
}



/**
 * Scales the current selection.
 */
void Grip::scale(Scene *scene, int command) {
	
	std::cout << "Grip::scale(Scene*,int)" << std::endl;
}



/**
 * Translates the current selection.
 */
void Grip::translate(Scene *scene, int command) {
	
	std::cout << "Grip::translate(Scene*,int)" << std::endl;
}

/*
 * Director.cpp
 *     Responsible for creating and storing scenes.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Director.hpp"



/**
 * Adds the commands this delegate supports and sets up handlers.
 */
Director::Director() {
	
	// Set type
	type = "Director";
	
	// Add zero-argument handlers
	handlersZero[Command::DESELECT] = &Director::select;
	handlersZero[Command::NEXT] = &Director::iterate;
	handlersZero[Command::PREVIOUS] = &Director::iterate;
	handlersZero[Command::SELECT_ALL] = &Director::select;
	
	// Add float-argument handlers
	handlersFloat[Command::GRAB] = &Director::grab;
}



/**
 * Picks an item in the scene based on coordinates.
 */
void Director::grab(Scene *scene, int cmd, float id) {
	
	Item *item;
	
	// Find item and set selected
	item = scene->getItem(static_cast<int>(id));
	if (item != NULL)
		item->toggleSelected();
}



/**
 * Iterates through the items in the scene.
 */
void Director::iterate(Scene *scene, int cmd) {
	
	std::cout << "Director::cmdIterate(Scene*,int)" << std::endl;
}



/**
 * Selects all or none.
 */
void Director::select(Scene *scene, int cmd) {
	
	switch (cmd) {
		case Command::SELECT_ALL :
			scene->selectAll();
			break;
		case Command::DESELECT :
			scene->deselectAll();
			break;
		default :
			break;
	}
	glutPostRedisplay();
}

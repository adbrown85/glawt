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
 * Picks an item in the scene by its ID number.
 */
void Director::grab(Scene *scene, int cmd, float id) {
	
	Identifiable *identifiable;
	Selectable *selectable;
	
	// Find item and set selected
	identifiable = Identifiable::findByID(static_cast<int>(id));
	if (identifiable != NULL) {
		selectable = dynamic_cast<Selectable*>(identifiable);
		if (selectable != NULL) {
			selectable->toggleSelected();
			if (selectable->isSelected())
				scene->selection.insert();
			else
				scene->selection.remove();
		}
	}
}



/**
 * Iterates through the items in the scene.
 * 
 * @bug Probably needs Scene to store lastSelectedShape.
 */
void Director::iterate(Scene *scene, int cmd) {
	
	std::cout << "Director::cmdIterate(Scene*,int)" << std::endl;
}



/**
 * Selects all or none.
 * 
 * @bug Wait for Selectable interface.
 */
void Director::select(Scene *scene, int cmd) {
	
	switch (cmd) {
		case Command::SELECT_ALL :
			std::cout << "Select All" << std::endl;
			break;
		case Command::DESELECT :
			std::cout << "Deselect All" << std::endl;
			break;
		default :
			break;
	}
	glutPostRedisplay();
}

/*
 * Director.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
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
void Director::grab(Scene *scene,
                    int cmd,
                    float id) {
	
	Identifiable *identifiable;
	Selectable *selectable;
	
	// Find item and set selected
	identifiable = Identifiable::findByID(static_cast<int>(id));
	if (identifiable != NULL) {
		selectable = dynamic_cast<Selectable*>(identifiable);
		if (selectable != NULL) {
			if (selectable->isSelected())
				scene->selection.remove(selectable);
			else
				scene->selection.add(selectable);
		}
	}
}


/**
 * Iterates through the items in the scene.
 * 
 * @bug Probably needs Scene to store lastSelectedShape.
 */
void Director::iterate(Scene *scene,
                       int cmd) {
	
	cout << "Director::cmdIterate(Scene*,int)" << endl;
}


/**
 * Selects all or none.
 * 
 * @bug Wait for Selectable interface.
 */
void Director::select(Scene *scene,
                      int cmd) {
	
	switch (cmd) {
		case Command::SELECT_ALL :
			scene->selection.addAll(&(scene->root));
			break;
		case Command::DESELECT :
			scene->selection.clear();
			break;
		default :
			break;
	}
	glutPostRedisplay();
}


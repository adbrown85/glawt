/*
 * Director.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Director.hpp"


/** Picks an item in the scene by its ID number. */
void Director::grab(int cmd, float id) {
	
	Identifiable *identifiable;
	Drawable *drawable;
	
	// Find item and set selected
	identifiable = Identifiable::findByID(static_cast<int>(id));
	if (identifiable != NULL) {
		drawable = dynamic_cast<Drawable*>(identifiable);
		if (drawable != NULL) {
			if (drawable->isSelected())
				scene->removeFromSelection(drawable);
			else
				scene->addToSelection(drawable);
		}
	}
}


/** Iterates through the items in the scene. */
void Director::iterate(int cmd) {
	
	cout << "Director::cmdIterate(Scene*,int)" << endl;
}


/** Selects all or none. */
void Director::select(int cmd) {
	
	switch (cmd) {
	case Command::SELECT_ALL :
		scene->addAllToSelection();
		break;
	case Command::DESELECT :
		scene->removeAllFromSelection();
		break;
	}
}


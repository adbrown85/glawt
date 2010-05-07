/*
 * Grip.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Grip.hpp"


/** Adds the handlers Grip supports. */
Grip::Grip() {
	
	// Set type
	type = "Grip";
	
	// Add float handlers
	handlersFloat[Command::ROTATE_X] = &Grip::rotate;
	handlersFloat[Command::ROTATE_Y] = &Grip::rotate;
	handlersFloat[Command::ROTATE_Z] = &Grip::rotate;
	handlersFloat[Command::SCALE_X] = &Grip::scale;
	handlersFloat[Command::SCALE_Y] = &Grip::scale;
	handlersFloat[Command::SCALE_Z] = &Grip::scale;
	handlersFloat[Command::TRANSLATE_X] = &Grip::translate;
	handlersFloat[Command::TRANSLATE_Y] = &Grip::translate;
	handlersFloat[Command::TRANSLATE_Z] = &Grip::translate;
}


/** Rotates the current selection. */
void Grip::rotate(Scene *scene,
                  int command,
                  float argument) {
	
	cout << "Grip::rotate(Scene*,int)" << endl;
}


/** Scales the current selection. */
void Grip::scale(Scene *scene,
                 int command,
                 float argument) {
	
	cout << "Grip::scale(Scene*,int)" << endl;
}


Translate* Grip::findTranslate(Node *node) {
	
	Node *currentNode=NULL;
	
	// Look for a Translate ancestor
	currentNode = node->getParent();
	while (currentNode != NULL) {
		if (typeid(*currentNode) == typeid(Translate))
			break;
		currentNode = currentNode->getParent();
	}
	return static_cast<Translate*>(currentNode);
}


/** Translates the current selection. */
void Grip::translate(Scene *scene,
                     int command,
                     float argument) {
	
	Node *node;
	Selection selection;
	Selection::iterator it;
	Translate *translation;
	Vector change;
	
	// Determine change
	switch(command) {
		case Command::TRANSLATE_X :
			change.x = argument;
			break;
		case Command::TRANSLATE_Y :
			change.y = argument;
			break;
		case Command::TRANSLATE_Z :
			change.z = argument;
			break;
	}
	
	// Apply change
	selection = scene->getSelection();
	for (it=selection.begin(); it!=selection.end(); ++it) {
		node = dynamic_cast<Node*>(*it);
		if (node != NULL) {
			translation = findTranslate(node);
			if (translation != NULL)
				translation->add(change);
		}
	}
}


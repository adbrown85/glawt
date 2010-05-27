/*
 * Grip.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Grip.hpp"


/** Stores the inputs. */
Grip::Grip(Scene *scene, Canvas *canvas) {
	
	this->scene = scene;
	this->canvas = canvas;
}


/** Rotates the current selection. */
void Grip::rotate(int command, float argument) {
	
	cout << "Grip::rotate(Scene*,int)" << endl;
}


/** Scales the current selection. */
void Grip::scale(int command, float argument) {
	
	Node *node;
	Selection selection;
	Selection::iterator it;
	Scale *scale;
	Vector change;
	
	// Determine change
	switch (command) {
	case Command::SCALE_X:
		change.x = argument;
		break;
	case Command::SCALE_Y:
		change.y = argument;
		break;
	case Command::SCALE_Z:
		change.z = argument;
		break;
	}
	
	// Apply change
	selection = scene->getSelection();
	for (it=selection.begin(); it!=selection.end(); ++it) {
		node = dynamic_cast<Node*>(*it);
		if (node != NULL) {
			scale = Scale::find(node);
			if (scale != NULL) {
				scale->add(change);
			}
		}
	}
}


/** Translates the current selection. */
void Grip::translate(int command, float argument) {
	
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
			translation = Translate::find(node);
			if (translation != NULL)
				translation->add(change);
		}
	}
}


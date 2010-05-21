/*
 * Sort.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Sort.hpp"


/** Sorts the translate nodes. */
void Sort::apply() {
	
	list<Translate*>::iterator it;
	
	rotation = Window::getRotationMatrix();
	for (it=translates.begin(); it!=translates.end(); ++it) {
		position = rotation * *(*it);
		(*it)->setDepth(position.z);
	}
	sort(children.begin(), children.end(), Node::compare);
}


/** Finds translate nodes. */
void Sort::associate() {
	
	vector<Node*>::iterator it;
	Translate *translate;
	
	// Store each translate node for sorting later
	for (it=children.begin(); it!=children.end(); ++it) {
		translate = dynamic_cast<Translate*>(*it);
		if (translate != NULL) {
			translates.push_back(translate);
		}
	}
}


/*
 * Blend.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Blend.hpp"


Blend::Blend(const Tag &tag) {
	
	
}


void Blend::apply() {
	
	glEnable(GL_BLEND);
	glDepthFunc(GL_ALWAYS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void Blend::associate() {
	
	list<Node*>::iterator it;
	Translation *translate;
	
	// Store each translate node
	for (it=children.begin(); it!=children.end(); ++it) {
		translate = dynamic_cast<Translation*>(*it);
		if (translate != NULL) {
			translates.push_back(translate);
		}
	}
}


void Blend::remove() {
	
	glDepthFunc(GL_LESS);
	glDisable(GL_BLEND);
}


/*
list<Node*> Blend::getChildren() const {
	
	list<Node*>::iterator it;
	Matrix rotation;
	Translation *translate;
	Vector position;
	
	rotation = Window::getRotationMatrix();
	for (it=children->begin(); it!=children->end(); ++it) {
		translate = dynamic_cast<Translation*>(*it);
		if (translate != NULL) {
			position = rotation * translate;
			it->setDepth(position.z);
		} else {
			it->setDepth(0.0);
		}
	}
	sort(children->begin(), children->end(), scompare);
}
*/


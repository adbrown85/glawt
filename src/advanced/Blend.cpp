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
	
	// Enable blending
	glEnable(GL_BLEND);
	glDepthFunc(GL_ALWAYS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Sort children
	sortChildren();
}


void Blend::associate() {
	
	vector<Node*>::iterator it;
	Translation *translate;
	
	// Store each translate node for sorting later
	for (it=children.begin(); it!=children.end(); ++it) {
		translate = dynamic_cast<Translation*>(*it);
		if (translate != NULL) {
			translates.push_back(translate);
		}
	}
}


void Blend::sortChildren() {
	
	list<Translation*>::iterator it;
	Matrix rotation;
	Vector position;
	
	rotation = Window::getRotationMatrix();
	for (it=translates.begin(); it!=translates.end(); ++it) {
		position = rotation * *(*it);
		(*it)->setDepth(position.z);
	}
	sort(children.begin(), children.end(), Node::compare);
}


void Blend::remove() {
	
	glDepthFunc(GL_LESS);
	glDisable(GL_BLEND);
}


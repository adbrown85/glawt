/*
 * SimpleTransformable.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "SimpleTransformable.hpp"



SimpleTransformable::SimpleTransformable(const Tag &tag) : Node(tag) {
	
	this->valid = false;
}



void SimpleTransformable::associate() {
	
	list<Transform*>::iterator it;
	
	// Find transforms and update position
	transforms.clear();
	Transform::findAll(getParent(), transforms);
	for (it=transforms.begin(); it!=transforms.end(); ++it) {
		(*it)->addListener(this, NodeEvent::MODIFY);
	}
	updatePositionExtent();
}


/** @return Model-matrix position of the item in the scene.
 * 
 * Lazily calculates the position only when requested and the position is 
 * determined to be invalid.  Currently this is implemented by adding 
 * listeners to all the Transform ancestors of the shape.  When one of the 
 * transforms is modified a flag is set to invalid.  After the position is 
 * requested and calculated again the flag is set to valid.  This way it can 
 * be requested multiple times but only calculated once when it is needed.
 * 
 * @note To find the depth of the shape on screen, multiply this value by the 
 * current canvas' rotation matrix and take the <i>z</i> component.
 */
Vector SimpleTransformable::getPosition() {
	
	if (!valid) {
		updatePositionExtent();
	}
	return position;
}


/** @return Model-matrix boundaries of the item in the scene.
 * 
 * @see getPosition()
 */
Extent SimpleTransformable::getExtent() {
	
	if (!valid) {
		updatePositionExtent();
	}
	return extent;
}


/** Updates the position and extent, then validates the position. */
void SimpleTransformable::updatePositionExtent() {
	
	Matrix matrix;
	list<Transform*>::iterator it;
	Vector point;
	float v[2]={-0.5,+0.5};
	
	// Concatenate transformations
	for (it=transforms.begin(); it!=transforms.end(); ++it) {
		(*it)->applyTo(matrix);
	}
	
	// Calculate extent and position
	extent.upper = Vector(-FLT_MAX, -FLT_MAX, -FLT_MAX, 1);
	extent.lower = Vector(+FLT_MAX, +FLT_MAX, +FLT_MAX, 1);
	for (int i=0; i<2; ++i) {
		for (int j=0; j<2; ++j) {
			for (int k=0; k<2; ++k) {
				point = matrix * Vector(v[i],v[j],v[k],1);
				extent.upper = max(extent.upper, point);
				extent.lower = min(extent.lower, point);
			}
		}
	}
	extent.diagonal = extent.upper - extent.lower;
	position = (extent.upper + extent.lower) * 0.5;
	
	// Extent and position are valid until a transform changes
	valid = true;
}


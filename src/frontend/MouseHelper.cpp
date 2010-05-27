/*
 * MouseHelper.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "MouseHelper.hpp"


MouseHelper::MouseHelper(Delegate *delegate) : Control(delegate) {
	
	type = "MouseHelper";
	data = NULL;
}


int MouseHelper::getModifier() {
	
	// Get modifiers from canvas
	return canvas->getModifier();
}


void MouseHelper::setData(MouseData *data) {
	
	this->data = data;
}


void MouseHelper::updateCurrentData(int x, int y) {
	
	data->x = x;
	data->y = y;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &(data->z));
}


void MouseHelper::updateLastData() {
	
	data->lastPosition.set(data->x, data->y, data->z);
}


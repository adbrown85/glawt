/*
 * MouseHelper.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "MouseHelper.hpp"


MouseHelper::MouseHelper(Delegate *delegate,
                         Scene *scene) :
                         Control(delegate, scene) {
	
	type = "MouseHelper";
	data = NULL;
}


int MouseHelper::getModifier() {
	
	int modifier;
	
	// Get modifiers from GLUT and remove Shift
	modifier = glutGetModifiers();
	if (modifier == 1 || modifier == 5)
		modifier -= 1;
	return modifier;
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


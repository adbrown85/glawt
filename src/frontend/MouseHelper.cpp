/*
 * MouseHelper.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "MouseHelper.hpp"



MouseHelper::MouseHelper(Delegate *delegate) :
                         Control(delegate) {
	
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



void MouseHelper::initialize(vector<Manipulator*> manipulators) {
	
	this->manipulators = manipulators;
}



void MouseHelper::initialize(MouseData *data) {
	
	this->data = data;
}



vector<Manipulator*> MouseHelper::install(Scene *scene) {
	
	this->scene = scene;
	return manipulators;
}



void MouseHelper::updateCurrentData(int x, int y) {
	
	data->x = x;
	data->y = y;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &(data->z));
}



void MouseHelper::updateLastData() {
	
	data->lastPosition.set(data->x, data->y, data->z);
	data->lastGlobalPosition = data->globalPosition;
}

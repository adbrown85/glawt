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
	print();
	return manipulators;
}


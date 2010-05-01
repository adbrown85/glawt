/*
 * MouseDragHelper.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "MouseDragHelper.hpp"
char MouseDragHelper::directions[2] = {'x', 'y'};


/**
 * Creates a new MouseDragHelper control.
 */
MouseDragHelper::MouseDragHelper(Interpreter *interpreter) :
                                 MouseHelper(interpreter) {
	
	type = "MouseDragHelper";
}


/**
 * Decides which axis the user should be allowed to drag in.
 * 
 * Waits a few iterations before deciding to make sure it matches the direction 
 * the user is actually dragging in.
 */
void MouseDragHelper::decideAxis() {
	
	// Dragging should be constrained
	if (useConstrained()) {
		
		// Reset axis and direction on first call
		if (data->iteration == 1) {
			axis.set(0.0, 0.0);
			direction.set(0.0, 0.0);
		}
		
		// Always update direction
		direction = direction + movement;
		
		// Wait for direction to increase before deciding on axis
		if (data->iteration < 10 && direction.length() >= 3.0) {
			if (fabs(direction.y) > fabs(direction.x))
				axis.set(0.0, 1.0);
			else
				axis.set(1.0, 0.0);
		}
	}
	
	// Allow both directions
	else
		axis.set(1.0, 1.0);
}


/**
 * Manipulates the scene when the mouse is dragged.
 * 
 * @param x Current horizontal coordinate of mouse while it's being dragged.
 * @param y Current vertical coordinate of mouse while it's being dragged.
 */
void MouseDragHelper::onDrag(int x,
                             int y) {
	
	// Update current mouse data
	updateCurrentData(x, y);
	++(data->iteration);
	movement.set( (x - data->lastPosition.x),
	             -(y - data->lastPosition.y));
	
	// Dragging a manipulator
	if (data->manipulator != NULL)
		data->manipulator->use(scene, movement, data->shapeID);
	
	// Dragging on the screen
	else {
		decideAxis();
		tryBindings();
	}
	
	// Finish
	updateLastData();
	glutPostRedisplay();
}


/**
 * Copies bindings from %Mouse that use drag into %MouseDragHelper.
 */
void MouseDragHelper::setBindings(multimap<int,Binding> bindings) {
	
	Binding *binding;
	multimap<int,Binding>::iterator pi;
	
	// Copy bindings with drag
	for (pi=bindings.begin(); pi!=bindings.end(); ++pi) {
		binding = &(pi->second);
		if (binding->hasDrag())
			add(*binding);
	}
}


void MouseDragHelper::tryBinding(Binding *binding) {
	
	char direction;
	float amount;
	
	// Ignore bindings that don't match conditions
	if (binding->getModifier() != data->modifier)
		return;
	
	// Try each direction
	direction = binding->getState();
	for (int i=0; i<2; ++i) {
		if (direction != directions[i])
			continue;
		
		// Determine amount to drag
		amount = movement.get(i) * 
		         axis.get(i) *
		         (fabs(Window::getPosition().z) / 45 * 1.75 + 1.0) *
		         binding->getArgument();
		
		// Run the command
		if (amount != 0.0)
			interpreter->run(binding->getCommand(), amount);
	}
}


void MouseDragHelper::tryBindings() {
	
	multimap<int,Binding>::iterator pi;
	pair<multimap<int,Binding>::iterator,
	     multimap<int,Binding>::iterator> range;
	
	// Try each binding for this button and modifier
	range = bindings.equal_range(data->button);
	for (pi=range.first; pi!=range.second; ++pi)
		tryBinding(&(pi->second));
}


/**
 * Checks if the dragging motion should be constrained to one direction.
 * 
 * @return True if it should be constrained.
 */
bool MouseDragHelper::useConstrained() {
	
	Binding *binding;
	multimap<int,Binding>::iterator pi;
	pair<multimap<int,Binding>::iterator,
	     multimap<int,Binding>::iterator> range;
	
	// Check each binding for this button
	range = bindings.equal_range(data->button);
	for (pi=range.first; pi!=range.second; ++pi) {
		binding = &(pi->second);
		if (binding->getCommand() == Command::CIRCLE_X
		      || binding->getCommand() == Command::CIRCLE_Y) {
			return true;
		}
	}
	return false;
}


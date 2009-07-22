/*
 * MouseClickHelper.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "MouseClickHelper.hpp"



MouseClickHelper::MouseClickHelper(Delegate *delegate) :
                                   MouseHelper(delegate) {
	type = "MouseClickHelper";
}



void MouseClickHelper::initialize(multimap<int,Binding> bindings) {
	
	Binding *binding;
	multimap<int,Binding>::iterator pi;
	
	// Add bindings without drag
	for (pi=bindings.begin(); pi!=bindings.end(); ++pi) {
		binding = &(pi->second);
		if (!binding->hasDrag())
			add(*binding);
	}
}



/**
 * Handles mouse clicks.
 * 
 * Note that because of limitations with GLUT, we treat rotating the mouse 
 * wheel as two separate buttons, defined in %Binding as <i>GLUT_UP_BUTTON</i> 
 * and <i>GLUT_DOWN_BUTTON</i>.
 * 
 * @param button
 *     Button that was clicked.
 * @param state
 *     State of the button.
 * @param x
 *     Current horizontal coordinate of the mouse when it was clicked.
 * @param y
 *     Current vertical coordinate of the mouse when it was clicked.
 */
void MouseClickHelper::onClick(int button,
                               int state,
                               int x,
                               int y) {
	
	// Update current mouse data
	data->modifier = getModifier();
	data->button = button;
	data->state = state;
	data->x = x;
	data->y = y;
	data->iteration = 0;
	
	// Pick the item under the cursor
	pickItem();
	
	// Try bindings for this button
	tryBindings();
	
	// Store cursor position for next time
	data->lastPosition.set(x, y);
}



/**
 * Finds the ID of the item under the cursor.
 * 
 * Stores the ID of the item under the cursor as 'currentItemID'.  Also sets 
 * 'currentManipulator' to the item's memory address if it is a manipulator.
 * If nothing is picked, 'UINT_MAX' is used for the former, and 'NULL' for the 
 * latter.
 */
void MouseClickHelper::pickItem() {
	
	Identifiable *identifiable;
	
	// Initialize
	data->manipulator = NULL;
	
	// For normal clicks
	if (data->button == GLUT_LEFT_BUTTON ||
	    data->button == GLUT_MIDDLE_BUTTON ||
	    data->button == GLUT_RIGHT_BUTTON) {
		
		// Pick the item
		data->itemID = Picker::pick(scene,
		                            manipulators,
		                            data->x,
		                            data->y);
		
		// Check if a manipulator
		identifiable = Identifiable::findByID(data->itemID);
		if (identifiable != NULL)
			data->manipulator = dynamic_cast<Manipulator*>(identifiable);
	}
}




/**
 * Issue the command for bindings if they match the current conditions.
 */
void MouseClickHelper::tryBindings() {
	
	multimap<int,Binding>::iterator bi;
	pair<multimap<int,Binding>::iterator,
	     multimap<int,Binding>::iterator> range;
	
	// Try each binding for this button
	range = bindings.equal_range(data->button);
	for (bi=range.first; bi!=range.second; ++bi)
		tryBinding(&(bi->second));
}



/**
 * Issue the command for a binding if it matches the current conditions.
 * 
 * @param binding
 *     Pointer to a %Binding.
 */
void MouseClickHelper::tryBinding(Binding *binding) {
	
	char direction;
	int modifier;
	
	// Ignore bindings that don't match current conditions
	if (binding->getModifier() != data->modifier)
		return;
	if (binding->getState() != data->state)
		return;
	if (data->manipulator != NULL)
		return;
	
	// Issue the command
	if (binding->hasArgument())
		delegate->run(binding->getCommand(),
		              binding->getArgument());
	else
		delegate->run(binding->getCommand());
	glutPostRedisplay();
}

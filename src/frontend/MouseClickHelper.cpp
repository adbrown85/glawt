/*
 * MouseClickHelper.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "MouseClickHelper.hpp"


/** Creates a new MouseClickHelper control. */
MouseClickHelper::MouseClickHelper(Interpreter *interpreter) :
                                   MouseHelper(interpreter),
                                   picker(scene,canvas) {
	
	type = "MouseClickHelper";
}


/** Handles mouse clicks.
 * 
 * Note that because of limitations with GLUT, we treat rotating the mouse 
 * wheel as two separate buttons, defined in %Binding as <i>GLUT_UP_BUTTON</i> 
 * and <i>GLUT_DOWN_BUTTON</i>.
 * 
 * @param button Button that was clicked.
 * @param state State of the button.
 * @param x Current horizontal coordinate of mouse when it was clicked.
 * @param y Current vertical coordinate of mouse when it was clicked.
 */
void MouseClickHelper::onClick(int button, int state, int x, int y) {
	
	// Update current mouse data
	data->modifier = getModifier();
	data->button = button;
	data->state = state;
	data->iteration = 0;
	updateCurrentData(x, y);
	
	// Pick item and try bindings
	pickItem();
	tryBindings();
	
	// Store positions for next time
	updateLastData();
}


/** Finds the ID of the item under the cursor and the item it was attached to.
 * 
 * Stores the ID of the item under the cursor as 'data->itemID' and the item 
 * it's attached to as 'data->shapeID'.  Also sets 'data->manipulator' to the 
 * item's memory address if it is a manipulator.  If nothing is picked, 
 * 'UINT_MAX' is used for the former, and 'NULL' for the latter.
 */
void MouseClickHelper::pickItem() {
	
	Identifiable *identifiable;
	pair<GLuint,GLuint> result;
	
	// Initialize
	data->manipulator = NULL;
	
	// For normal clicks
	if (data->button == CANVAS_LEFT_BUTTON
	      || data->button == CANVAS_MIDDLE_BUTTON
	      || data->button == CANVAS_RIGHT_BUTTON) {
		
		// Pick the item
		result = picker.pick(data->x, data->y);
		data->itemID = result.first;
		data->shapeID = result.second;
		
		// Check if a manipulator
		identifiable = Identifiable::findByID(data->itemID);
		if (identifiable != NULL)
			data->manipulator = dynamic_cast<Manipulator*>(identifiable);
	}
}


/** Copies bindings from %Mouse that do not have drag. */
void MouseClickHelper::setBindings(multimap<int,Binding> bindings) {
	
	Binding *binding;
	multimap<int,Binding>::iterator pi;
	
	// Add bindings without drag
	for (pi=bindings.begin(); pi!=bindings.end(); ++pi) {
		binding = &(pi->second);
		if (!binding->hasDrag())
			add(*binding);
	}
}


/** Stores the manipulators and passes them to picker. */
void MouseClickHelper::setManipulators(vector<Manipulator*> manipulators) {
	
	Control::setManipulators(manipulators);
	picker.addManipulators(manipulators);
}


/** Issue the command for bindings if they match the current conditions. */
void MouseClickHelper::tryBindings() {
	
	multimap<int,Binding>::iterator bi;
	pair<multimap<int,Binding>::iterator,
	     multimap<int,Binding>::iterator> range;
	
	// Try each binding for this button
	range = bindings.equal_range(data->button);
	for (bi=range.first; bi!=range.second; ++bi)
		tryBinding(&(bi->second));
}


/** Issue the command for a binding if it matches the current conditions. */
void MouseClickHelper::tryBinding(Binding *binding) {
	
	// Ignore bindings that don't match current conditions
	if (binding->getModifier() != data->modifier)
		return;
	if (binding->getState() != data->state)
		return;
	if (data->manipulator != NULL)
		return;
	
	// Issue the command
	if (binding->hasArgument()) {
		interpreter->run(binding->getCommand(), binding->getArgument());
	} else {
		interpreter->run(binding->getCommand());
	}
	canvas->refresh();
}


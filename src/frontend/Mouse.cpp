/*
 * Mouse.cpp
 *     Mouse control for a 3D display.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Mouse.hpp"
Mouse *Mouse::obj=NULL;



/**
 * GLUT callback for mouse clicks.
 */
void Mouse::clickCallback(int button,
                          int state,
                          int x,
                          int y) {
	
	obj->clickHandler(button, state, x, y);
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
void Mouse::clickHandler(int button,
                         int state,
                         int x,
                         int y) {
	
	char direction;
	int modifier;
	multimap<int,Binding>::iterator bi;
	pair<multimap<int,Binding>::iterator,
	     multimap<int,Binding>::iterator> range;
	
	// Pick the item under the cursor
	pickItem(button, x, y);
	
	// Reset dragging
	if (state == GLUT_DOWN) {
		dragBindings.clear();
		dragCount = 0;
	}
	
	// Try bindings for this button
	range = bindings.equal_range(button);
	for (bi=range.first; bi!=range.second; ++bi)
		tryBinding(&(bi->second), state);
	
	// Store cursor position for next time
	lastCursorPosition.set(x, y);
}



/**
 * Installs the control into the current context.
 * 
 * @param scene
 *     Makes the Control use this scene;
 */
vector<Manipulator*> Mouse::install(Scene *scene) {
	
	// Initialize attributes
	Mouse::obj = this;
	this->scene = scene;
	this->type = "Mouse";
	
	// Install
	installBindings();
	installCallbacks();
	installManipulators();
	print();
	
	// Finish
	return manipulators;
}



/**
 * Installs the bindings for the mouse.
 * 
 * @see Binding
 */
void Mouse::installBindings() {
	
	// Add bindings for mouse wheel
	add(Binding(GLUT_UP_BUTTON, 0, Command::ZOOM_IN, 1.0f, GLUT_DOWN));
	add(Binding(GLUT_DOWN_BUTTON, 0, Command::ZOOM_OUT, 1.0f, GLUT_DOWN));
	
	// Add bindings for left button
	add(Binding(GLUT_LEFT_BUTTON,
	            GLUT_ACTIVE_ALT,
	            Command::GRAB,
	            &currentItemID,
	            GLUT_DOWN));
	add(Binding(GLUT_LEFT_BUTTON,
	            GLUT_ACTIVE_ALT,
	            Command::MANIPULATE,
	            GLUT_DOWN));
	add(Binding(GLUT_LEFT_BUTTON,
	            0,
	            Command::CIRCLE_Y,
	            -1.0f,
	            'x'));
	add(Binding(GLUT_LEFT_BUTTON,
	            0,
	            Command::CIRCLE_X,
	            -1.0f,
	            'y'));
	
	// Add bindings for middle button
	add(Binding(GLUT_MIDDLE_BUTTON,
	            0,
	            Command::TRACK,
	            -1.0f,
	            'x'));
	add(Binding(GLUT_MIDDLE_BUTTON,
	            0,
	            Command::BOOM,
	            1.0f,
	            'y'));
}



/**
 * Installs the GLUT callbacks for the mouse.  Will register the callback 
 * functions for both clicks and drags with GLUT.
 */
void Mouse::installCallbacks() {
	
	// Register clicks and drags
	glutMouseFunc(Mouse::clickCallback);
	glutMotionFunc(Mouse::dragCallback);
}



/**
 * Installs the manipulators to show for selected items.  A class that uses 
 * the control should draw these manipulators for selected items.
 */
void Mouse::installManipulators() {
	
	// Add translators
	add(new Translator(1.0, 0.0, 0.0));
	add(new Translator(0.0, 1.0, 0.0));
	add(new Translator(0.0, 0.0, 1.0));
}



/**
 * GLUT callback for when the mouse is dragged.
 */
void Mouse::dragCallback(int x,
                         int y) {
	
	obj->dragHandler(x, y);
}



/**
 * Decides which axis the user should be allowed to drag in.  Waits a few 
 * screen coordinates before deciding to make sure it matches the direction 
 * the user is dragging in.
 */
void Mouse::dragDecideAxis(const Vector &movement) {
	
	// Dragging should be constrained
	if (dragUseConstrained()) {
		
		// Reset axis and direction on first call
		if (dragCount == 0) {
			dragAxis.set(0.0, 0.0);
			dragDirection.set(0.0, 0.0);
		}
		
		// Always update direction
		dragDirection = dragDirection + movement;
		
		// Wait for direction to increase before deciding on axis
		if (dragCount < 10 && dragDirection.length() >= 3.0) {
			if (dragAxis.x < 0.5 && dragAxis.y < 0.5) {
				if (fabs(dragDirection.y) > fabs(dragDirection.x))
					dragAxis.set(0.0, 1.0);
				else
					dragAxis.set(1.0, 0.0);
			}
		}
	}
	
	// Allow both directions
	else
		dragAxis.set(1.0, 1.0);
}



/**
 * Manipulates the scene when the mouse is dragged.
 * 
 * @param x
 *     Current horizontal coordinate of the mouse while it's being dragged.
 * @param y
 *     Current vertical coordinate of the mouse while it's being dragged.
 */
void Mouse::dragHandler(int x,
                        int y) {
	
	Binding *binding;
	char directions[] = {'x', 'y'};
	float dragAmount;
	map<char,Binding*>::iterator bi;
	Vector movement;
	
	// Determine movement from last update
	movement.set((x-lastCursorPosition.x), -(y-lastCursorPosition.y));
	
	// Dragging a manipulator
	if (currentManipulator != NULL)
		currentManipulator->use(scene, movement);
	
	// Dragging on the screen
	else {
		
		// Decide axis for dragging
		dragDecideAxis(movement);
		
		// Check drag bindings in both directions
		for (int i=0; i<2; i++) {
			bi = dragBindings.find(directions[i]);
			if (bi != dragBindings.end()) {
				binding = bi->second;
				if (binding != NULL) {
					if (fabs(movement.get(i)) > 0.99) {
						
						// Determine amount to drag
						dragAmount = movement.get(i) * 
						             dragAxis.get(i) *
						             binding->getArgument();
						
						// Run the command
						if (dragAmount != 0.0)
							delegate->run(binding->getCommand(), dragAmount);
					}
				}
			}
		}
	}
	
	// Update
	lastCursorPosition.set(x, y);
	++dragCount;
	glutPostRedisplay();
}



/**
 * Checks if the dragging motion should be constrained to one direction.
 * 
 * @return
 *     True if it should be constrained.
 */
bool Mouse::dragUseConstrained() {
	
	Binding *binding;
	char directions[] = {'x', 'y'};
	map<char,Binding*>::iterator bi;
	
	// Check both 'x' and 'y' directions
	for (int i=0; i<2; ++i) {
		
		// Temporarily store binding for this direction
		bi = dragBindings.find(directions[i]);
		if (bi != dragBindings.end()) {
			binding = bi->second;
			if (binding != NULL) {
				
				// Check if command should be constrained
				if (binding->getCommand() == Command::CIRCLE_X ||
				    binding->getCommand() == Command::CIRCLE_Y)
					return true;
			}
		}
	}
	return false;
}



/**
 * Stores the ID of the item under the cursor as 'currentItemID'.  Also sets 
 * 'currentManipulator' to the item's memory address if it is a manipulator.
 * If nothing is picked, 'UINT_MAX' is used for the former, and 'NULL' for the 
 * latter.
 * 
 * @param button
 *     Mouse button clicked.
 */
void Mouse::pickItem(int button,
                     int x,
                     int y) {
	
	Identifiable *identifiable;
	
	// Initialize
	currentManipulator = NULL;
	
	// For normal clicks
	if (button == GLUT_LEFT_BUTTON ||
	    button == GLUT_MIDDLE_BUTTON ||
	    button == GLUT_RIGHT_BUTTON) {
		
		// Pick the item
		currentItemID = Picker::pick(scene, manipulators, x, y);
		
		// Check if a manipulator
		identifiable = Identifiable::findByID(currentItemID);
		if (identifiable != NULL)
			currentManipulator = dynamic_cast<Manipulator*>(identifiable);
	}
}



/**
 * Issue the command for a binding if it matches the current conditions.
 * 
 * @param binding
 *     Pointer to a %Binding.
 * @param state
 *     State of the button clicked.
 */
void Mouse::tryBinding(Binding *binding,
                       int state) {
	
	char direction;
	int modifier;
	
	// Ignore bindings that don't match the current modifier
	modifier = glutGetModifiers();
	if (modifier == 1 || modifier == 5)
		modifier -= 1;
	if (binding->getModifier() != modifier)
		return;
	
	// Store the binding if it's meant for dragging
	if (binding->hasDrag()) {
		direction = static_cast<char>(binding->getState());
		if (state == GLUT_DOWN)
			dragBindings[direction] = binding;
		else
			dragBindings[direction] = NULL;
		return;
	}
	
	// Issue the command if the state matches
	if (state == binding->getState()) {
		if (currentManipulator==NULL) {
			if (binding->hasArgument())
				delegate->run(binding->getCommand(),
				              binding->getArgument());
			else
				delegate->run(binding->getCommand());
			glutPostRedisplay();
		}
	}
}


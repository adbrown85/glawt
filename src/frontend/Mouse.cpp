/*
 * Mouse.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Mouse.hpp"


Mouse::Mouse(Delegate *delegate) : Control(delegate), picker(scene,canvas) {
	
	list<Manipulator*>::iterator it;
	
	// Set name
	this->type = "Mouse";
	
	// Add bindings and manipulators
	addManipulators();
	addBindings();
	enableTranslateManipulators();
	for (it=manips.begin(); it!=manips.end(); ++it)
		(*it)->setDelegate(delegate);
	
	// Set up picking
	picker.addManipulators(manips);
	
	// Add listeners
	delegate->addListener(this, Command::TRANSLATE);
	delegate->addListener(this, Command::SCALE);
	delegate->addListener(this, Command::ROTATE);
}


void Mouse::dragApply() {
	
	float amount;
	
	// Apply drag in both directions
	for (int i=0; i<2; ++i) {
		if (dragBindings[i] == NULL)
			continue;
		amount = findDragAmount(i);
		if (fabs(amount) > 0.001)
			delegate->run(dragBindings[i]->getCommand(), amount);
	}
}


/** Decides which axis the user should be allowed to drag in. */
void Mouse::dragDecide() {
	
	char labels[2]={'x','y'};
	
	// Find the bindings for each axis direction
	axis.set(1.0, 1.0);
	for (int i=0; i<2; ++i) {
		state.combo.action = labels[i];
		dragBindings[i] = getBinding(state.combo);
	}
	
	// Unset one of the bindings if can't use unconstrained
	for (int i=0; i<2; ++i) {
		if (dragBindings[i] != NULL) {
			if (fabs(direction[i]) > fabs(direction[!i])) {
				if (!useUnconstrained(dragBindings[i]->getCommand())) {
					axis.set(0.0, 0.0);
					axis[i] = 1.0;
					dragBindings[!i] = NULL;
					break;
				}
			}
		}
	}
}


/** Use all the scale manipulators. */
void Mouse::enableScaleManipulators() {
	
	list<Manipulator*>::iterator it;
	
	for (it=manips.begin(); it!=manips.end(); ++it) {
		switch ((*it)->getCommand()) {
		case Command::SCALE_X:
		case Command::SCALE_Y:
		case Command::SCALE_Z:
			(*it)->setEnabled(true);
			break;
		default:
			(*it)->setEnabled(false);
		}
	}
}


/** Use all the translate manipulators. */
void Mouse::enableTranslateManipulators() {
	
	list<Manipulator*>::iterator it;
	
	for (it=manips.begin(); it!=manips.end(); ++it) {
		switch ((*it)->getCommand()) {
		case Command::TRANSLATE_X:
		case Command::TRANSLATE_Y:
		case Command::TRANSLATE_Z:
			(*it)->setEnabled(true);
			break;
		default:
			(*it)->setEnabled(false);
		}
	}
}


float Mouse::findDragAmount(int i) {
	
	float factor;
	
	factor = canvas->getCamera()->getPosition().z * -0.15;
	return movement[i] * axis[i] * factor * dragBindings[i]->getArgument();
}


/** Installs the control into the current context. */
void Mouse::install() {
	
	canvas->addListener(this, CanvasEvent::BUTTON);
	canvas->addListener(this, CanvasEvent::DRAG);
}


/** Handles incoming events from the canvas. */
void Mouse::onCanvasEvent(const CanvasEvent &event) {
	
	switch (event.type) {
	case CanvasEvent::BUTTON:
		onCanvasEventButton(event);
		break;
	case CanvasEvent::DRAG:
		onCanvasEventDrag(event);
		break;
	}
}


/** Handles mouse clicks. */
void Mouse::onCanvasEventButton(const CanvasEvent &event) {
	
	// Update
	state = event.state;
	binding = getBinding(state.combo);
	
	// Reset dragging
	iteration = 0;
	axis.set(0.0, 0.0);
	direction.set(0.0, 0.0);
	
	// Pick item for normal clicks
	if (state.combo.trigger != CANVAS_WHEEL_DOWN
	      && state.combo.trigger != CANVAS_WHEEL_UP) {
		pickItem();
	}
	
	// Run binding
	if (binding != NULL) {
		if (binding->hasArgument()) {
			delegate->run(binding->getCommand(), binding->getArgument());
		} else {
			delegate->run(binding->getCommand());
		}
	}
	
	// Finish
	last = state;
	canvas->refresh();
}


/** Handles mouse dragging. */
void Mouse::onCanvasEventDrag(const CanvasEvent &event) {
	
	// Update
	state = event.state;
	++iteration;
	movement.set((state.x-last.x), -(state.y-last.y));
	
	// Dragging a manipulator
	if (manip != NULL) {
		manip->use(movement, shapeID, canvas);
	}
	
	// Dragging on the screen
	else {
		if (iteration < 10) {
			direction = direction + movement;
		} else if (iteration == 10) {
			dragDecide();
		} else {
			dragApply();
		}
	}
	
	// Finish
	last = state;
	canvas->refresh();
}


/** Handles incoming events from the delegate. */
void Mouse::onCommandEvent(int command) {
	
	switch (command) {
	case Command::TRANSLATE:
		enableTranslateManipulators();
		break;
	case Command::SCALE:
		enableScaleManipulators();
		break;
	}
}


/** Finds the item ID and shape ID, and checks if item was manipulaor. */
void Mouse::pickItem() {
	
	Identifiable *identifiable;
	pair<GLuint,GLuint> result;
	
	// Initialize
	manip = NULL;
	
	// Pick the item
	result = picker.pick(state.x, state.y);
	itemID = result.first;
	shapeID = result.second;
	
	// Check if a manipulator
	identifiable = Identifiable::findByID(itemID);
	if (identifiable != NULL)
		manip = dynamic_cast<Manipulator*>(identifiable);
}


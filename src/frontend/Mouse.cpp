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
	
	// Set up picking and dragging
	picker.addManipulators(manips);
	camera = canvas->getCamera();
	
	// Add listeners
	canvas->addListener(this, CanvasEvent::BUTTON);
	canvas->addListener(this, CanvasEvent::DRAG);
	delegate->addListener(this, Command::TRANSLATE);
	delegate->addListener(this, Command::SCALE);
	delegate->addListener(this, Command::ROTATE);
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
	
	factor = fabs(camera->getPosition().z) / 80 + 1;
	return movement[i] * axis[i] * factor * binding->getArgument();
}


/** Installs the control into the current context. */
void Mouse::install() {
	
	// Register callbacks
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
	glReadPixels(state.x,state.y, 1,1, GL_DEPTH_COMPONENT, GL_FLOAT, &(depth));
	
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
}


/** Handles mouse dragging. */
void Mouse::onCanvasEventDrag(const CanvasEvent &event) {
	
	float amount;
	int i;
	
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
			decideAxis();
		} else {
			if (axis.x > 1.0) {
				state.combo.action = 'x';
				i = 0;
			} else if (axis.y > 1.0) {
				state.combo.action = 'y';
				i = 1;
			}
			binding = getBinding(state.combo);
			amount = findDragAmount(i);
			if (amount > 0.001) {
				delegate->run(binding->getCommand(), amount);
			}
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


/** Decides which axis the user should be allowed to drag in. */
void Mouse::decideAxis() {
	
	// Wait for direction to increase before deciding on axis
	if (direction.length() >= 3.0) {
		direction = direction + movement;
		if (fabs(direction.y) > fabs(direction.x))
			axis.set(0.0, 1.0);
		else
			axis.set(1.0, 0.0);
	}
}


/** @return True if dragging motion should be constrained to one direction. */
/*
bool Mouse::useConstrained() {
	
	Binding *binding;
	map<Combo,>::iterator it;
	
	it = bindings.find(state.combo);
	if (it != bindings.end()) {
		binding = &(it->second);
		return (binding->getCommand() == Command::CIRCLE_X) ||
		       (binding->getCommand() == Command::CIRCLE_Y)
	}
	return false;
}
*/


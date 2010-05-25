/*
 * Mouse.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Mouse.hpp"
Mouse *Mouse::obj=NULL;


Mouse::Mouse(Interpreter *interpreter) : Control(interpreter),
                                         clickHelper(interpreter),
                                         dragHelper(interpreter) {
	
	Mouse::obj = this;
	
	this->type = "Mouse";
	initBindings();
	initData();
	initManipulators();
}


/** Installs the control into the current context. */
void Mouse::install() {
	
	// Register callbacks
	canvas->setMouseCallback(Mouse::onClick);
	canvas->setDragCallback(Mouse::onDrag);
	
	// Install helpers
	clickHelper.install();
	dragHelper.install();
}


/** Installs the bindings for the mouse. */
void Mouse::initBindings() {
	
	// Add bindings for mouse wheel
	add(Binding(CANVAS_WHEEL_UP, 0, Command::ZOOM_IN, 1.0f, CANVAS_UP));
	add(Binding(CANVAS_WHEEL_DOWN, 0, Command::ZOOM_OUT, 1.0f, CANVAS_UP));
	
	// Add bindings for left button
	add(Binding(CANVAS_LEFT_BUTTON,
	            CANVAS_MOD_CONTROL,
	            Command::GRAB,
	            &(data.itemID),
	            CANVAS_DOWN));
	add(Binding(CANVAS_LEFT_BUTTON,
	            0,
	            Command::CIRCLE_Y,
	            -1.0f,
	            'x'));
	add(Binding(CANVAS_LEFT_BUTTON,
	            0,
	            Command::CIRCLE_X,
	            -1.0f,
	            'y'));
	
	// Add bindings for middle button
	add(Binding(CANVAS_MIDDLE_BUTTON,
	            0,
	            Command::TRACK,
	            -1.0f,
	            'x'));
	add(Binding(CANVAS_MIDDLE_BUTTON,
	            0,
	            Command::BOOM,
	            1.0f,
	            'y'));
	
	// Copy to helpers
	clickHelper.setBindings(bindings);
	dragHelper.setBindings(bindings);
}


/** Shares the mouse data with the helpers. */
void Mouse::initData() {
	
	clickHelper.setData(&data);
	dragHelper.setData(&data);
}


/** Installs the manipulators to show for selected items. */
void Mouse::initManipulators() {
	
	// Add
	add(new Manipulator('x', Command::TRANSLATE_X, "ui/TranslateX.xml"));
	add(new Manipulator('y', Command::TRANSLATE_Y, "ui/TranslateY.xml"));
	add(new Manipulator('z', Command::TRANSLATE_Z, "ui/TranslateZ.xml"));
	add(new Manipulator('x', Command::SCALE_X, "ui/ScaleX.xml", 2));
	add(new Manipulator('y', Command::SCALE_Y, "ui/ScaleY.xml", 2));
	add(new Manipulator('z', Command::SCALE_Z, "ui/ScaleZ.xml", 2));
	
	// Initialize
	enableTranslateManipulators();
	for (size_t i=0; i<manipulators.size(); ++i) {
		manipulators[i]->setInterpreter(interpreter);
	}
	clickHelper.setManipulators(manipulators);
	dragHelper.setManipulators(manipulators);
	
	// Add listeners
	interpreter->addListener(Command::TRANSLATE, &onModeChange);
	interpreter->addListener(Command::SCALE, &onModeChange);
	interpreter->addListener(Command::ROTATE, &onModeChange);
}


/** GLUT callback for mouse clicks. */
void Mouse::onClick(int button, int state, int x, int y) {
	
	obj->clickHelper.onClick(button, state, x, y);
}


/** GLUT callback for when the mouse is dragged. */
void Mouse::onDrag(int x, int y) {
	
	obj->dragHelper.onDrag(x, y);
}


void Mouse::onModeChange(int command) {
	
	switch (command) {
	case Command::TRANSLATE:
		obj->enableTranslateManipulators();
		break;
	case Command::SCALE:
		obj->enableScaleManipulators();
		break;
	}
}


void Mouse::enableScaleManipulators() {
	
	vector<Manipulator*>::iterator it;
	
	for (it=manipulators.begin(); it!=manipulators.end(); ++it) {
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


void Mouse::enableTranslateManipulators() {
	
	vector<Manipulator*>::iterator it;
	
	for (it=manipulators.begin(); it!=manipulators.end(); ++it) {
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


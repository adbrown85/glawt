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
	glutMouseFunc(Mouse::onClick);
	glutMotionFunc(Mouse::onDrag);
	
	// Install helpers
	clickHelper.install();
	dragHelper.install();
}


/** Installs the bindings for the mouse. */
void Mouse::initBindings() {
	
	// Add bindings for mouse wheel
	add(Binding(GLUT_UP_BUTTON, 0, Command::ZOOM_IN, 1.0f, GLUT_DOWN));
	add(Binding(GLUT_DOWN_BUTTON, 0, Command::ZOOM_OUT, 1.0f, GLUT_DOWN));
	
	// Add bindings for left button
	add(Binding(GLUT_LEFT_BUTTON,
	            GLUT_ACTIVE_ALT,
	            Command::GRAB,
	            &(data.itemID),
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
	add(new Translator(1.0, 0.0, 0.0));
	add(new Translator(0.0, 1.0, 0.0));
	add(new Translator(0.0, 0.0, 1.0));
	add(new Scaler(1.0, 0.0, 0.0));
	add(new Scaler(0.0, 1.0, 0.0));
	add(new Scaler(0.0, 0.0, 1.0));
	
	// Enable scalers
	enableTranslators();
	
	// Set interpreter
	for (size_t i=0; i<manipulators.size(); ++i) {
		manipulators[i]->setInterpreter(interpreter);
	}
	
	// Copy to helpers
	clickHelper.setManipulators(manipulators);
	dragHelper.setManipulators(manipulators);
	
	// Add listeners
	interpreter->addListener(Command::TRANSLATE, &onModeChange);
	interpreter->addListener(Command::SCALE, &onModeChange);
	interpreter->addListener(Command::ROTATE, &onModeChange);
}


/** GLUT callback for mouse clicks. */
void Mouse::onClick(int button, int state, int x, int y) {
	
	// Pass to click helper
	obj->clickHelper.onClick(button, state, x, y);
}


/** GLUT callback for when the mouse is dragged. */
void Mouse::onDrag(int x, int y) {
	
	// Pass to drag helper
	obj->dragHelper.onDrag(x, y);
}


void Mouse::onModeChange(int command) {
	
	switch (command) {
	case Command::TRANSLATE:
		obj->enableTranslators();
		break;
	case Command::SCALE:
		obj->enableScalers();
		break;
	}
}


void Mouse::enableScalers() {
	
	Scaler *scaler;
	vector<Manipulator*>::iterator it;
	
	for (it=manipulators.begin(); it!=manipulators.end(); ++it) {
		scaler = dynamic_cast<Scaler*>(*it);
		if (scaler != NULL) {
			(*it)->setEnabled(true);
		} else {
			(*it)->setEnabled(false);
		}
	}
}


void Mouse::enableTranslators() {
	
	Translator *translator;
	vector<Manipulator*>::iterator it;
	
	for (it=manipulators.begin(); it!=manipulators.end(); ++it) {
		translator = dynamic_cast<Translator*>(*it);
		if (translator != NULL) {
			(*it)->setEnabled(true);
		} else {
			(*it)->setEnabled(false);
		}
	}
}


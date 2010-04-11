/*
 * Mouse.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Mouse.hpp"
Mouse *Mouse::obj=NULL;


/**
 * Installs the control into the current context.
 * 
 * @param scene Makes the Control use this scene;
 */
vector<Manipulator*> Mouse::install(Scene *scene) {
	
	MouseHelper *helpers[2];
	
	// Initialize attributes
	Mouse::obj = this;
	this->scene = scene;
	this->type = "Mouse";
	
	// Install
	installBindings();
	installCallbacks();
	installManipulators();
	
	// Copy to helpers
	helpers[0] = &clickHelper;
	helpers[1] = &dragHelper;
	for (int i=0; i<2; ++i) {
		helpers[i]->initialize(bindings);
		helpers[i]->initialize(manipulators);
		helpers[i]->initialize(&data);
		helpers[i]->install(scene);
	}
	
	// Finish
	print();
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
}


/**
 * Installs the GLUT callbacks for the mouse.
 * 
 * Will register the callback functions for both clicks and drags with GLUT.
 */
void Mouse::installCallbacks() {
	
	// Register clicks and drags
	glutMouseFunc(Mouse::onClick);
	glutMotionFunc(Mouse::onDrag);
}


/**
 * Installs the manipulators to show for selected items.
 * 
 * A class that uses the control should draw these manipulators for selected 
 * items.
 */
void Mouse::installManipulators() {
	
	// Add translators
	add(new Translator(1.0, 0.0, 0.0));
	add(new Translator(0.0, 1.0, 0.0));
	add(new Translator(0.0, 0.0, 1.0));
	
	// Set delegates
	for (size_t i=0; i<manipulators.size(); ++i) {
		manipulators[i]->setDelegate(delegate);
	}
}


/**
 * GLUT callback for mouse clicks.
 */
void Mouse::onClick(int button,
                    int state,
                    int x,
                    int y) {
	
	// Pass to click helper
	obj->clickHelper.onClick(button, state, x, y);
}


/**
 * GLUT callback for when the mouse is dragged.
 */
void Mouse::onDrag(int x,
                   int y) {
	
	// Pass to drag helper
	obj->dragHelper.onDrag(x, y);
}


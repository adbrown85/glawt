/*
 * Control.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Control.hpp"


/**
 * Creates a new control using the specified Delegate to run commands.
 * 
 * @param delegate Pointer to a Delegate that runs
 * @param scene Pointer to the collection of nodes
 */
Control::Control(Delegate *delegate,
                 Scene *scene) {
	
	// Initialize
	this->delegate = delegate;
	this->scene = scene;
}


/**
 * Deallocates the manipulators.
 */
Control::~Control() {
	
	// Delete each manipulator
	for (size_t i=0; i<manipulators.size(); ++i)
		delete manipulators[i];
}


/**
 * Adds a Binding to the control.
 * 
 * @param binding Binding to add (creates a copy).
 */
void Control::add(const Binding &binding) {
	
	bindings.insert(pair<int,Binding>(binding.getTrigger(), binding));
}


/**
 * Adds a Manipulator to the control.
 */
void Control::add(Manipulator *manipulator) {
	
	manipulators.push_back(manipulator);
}


vector<Manipulator*> Control::getManipulators() const {
	
	return manipulators;
}


/**
 * Print each Binding attached to the control.
 */
void Control::print() {
	
	multimap<int,Binding>::iterator bi;
	
	// Add type of control
	if (!type.empty())
		cout << type << " ";
	
	// Print each binding
	cout << "Bindings:" << endl;
	for (bi=bindings.begin(); bi!=bindings.end(); bi++)
		cout << "  " << bi->second << endl;
}


void Control::setManipulators(vector<Manipulator*> manipulators) {
	
	this->manipulators = manipulators;
}


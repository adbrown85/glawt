/*
 * Control.cpp
 *     Interface for a display control.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Control.hpp"



/**
 * Creates a new Control using the specified Delegate to run commands.
 * 
 * @param delegate
 *     Pointer to a Delegate that runs 
 */
Control::Control(Delegate *delegate) {
	
	// Initialize
	this->delegate = delegate;
}



/**
 * Deallocates the manipulators.
 */
Control::~Control() {
	
	// Delete each manipulator
	for (int i=0; i<manipulators.size(); ++i)
		delete manipulators[i];
}



/**
 * Adds a Binding to the Control.
 * 
 * @param binding
 *     Binding to add.  Creates a copy.
 */
void Control::add(const Binding &binding) {
	
	// Insert the binding with its trigger
	bindings.insert(pair<int,Binding>(binding.getTrigger(),
	                                  binding));
}



/**
 * Adds a Manipulator to the control.
 */
void Control::add(Manipulator *manipulator) {
	
	// Add the manipulator
	manipulators.push_back(manipulator);
}



/**
 * Print each Binding attached to the Control.
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

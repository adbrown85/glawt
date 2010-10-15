/*
 * Control.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Control.hpp"


/** Creates a new control using the specified delegate to run commands. */
Control::Control(Delegate *delegate) {
	
	// Initialize
	this->delegate = delegate;
	this->scene = delegate->getScene();
	this->canvas = delegate->getCanvas();
}


/** Deallocates the manipulators. */
Control::~Control() {
	
	list<Manipulator*>::iterator it;
	
	// Delete each manipulator
	for (it=manips.begin(); it!=manips.end(); ++it)
		delete (*it);
	manips.clear();
}


/** Adds a Binding to the control. */
void Control::add(Binding binding) {
	
	bindings.insert(pair<Combo,Binding>(binding.getCombo(), binding));
}


/** Adds a Manipulator to the control. */
void Control::add(Manipulator *manip) {
	
	manips.push_back(manip);
}


Binding* Control::getBinding(const Combo& combo) {
	
	map<Combo,Binding>::iterator it;
	
	it = bindings.find(combo);
	if (it != bindings.end()) {
		return &(it->second);
	} else {
		return NULL;
	}
}


/** Print each Binding attached to the control. */
void Control::print() {
	
	map<Combo,Binding>::iterator it;
	
	// Add type of control
	if (!type.empty())
		cout << type << " ";
	
	// Print each binding
	cout << "Bindings:" << endl;
	for (it=bindings.begin(); it!=bindings.end(); ++it)
		cout << "  " << it->second.toString() << endl;
}


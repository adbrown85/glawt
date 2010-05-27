/*
 * Keyboard.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Keyboard.hpp"


Keyboard::Keyboard(Delegate *delegate) : Control(delegate) {
	
	type = "Keyboard";
	addBindings();
}


/** Installs the controls into the current context. */
void Keyboard::install() {
	
	canvas->addListener(this, CanvasEvent::KEY);
}


/** Triggers a command. */
void Keyboard::onCanvasEvent(const CanvasEvent &event) {
	
	Binding *binding;
	map<Combo,Binding>::iterator it;
	
	// Lookup binding
	it = bindings.find(event.state.combo);
	if (it == bindings.end())
		return;
	
	// Run command with argument if it has one
	binding = &(it->second);
	if (binding->hasArgument())
		delegate->run(binding->getCommand(), binding->getArgument());
	else
		delegate->run(binding->getCommand());
	canvas->refresh();
}


/*
 * Binding.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <iostream>
#include "Binding.hpp"
bool Binding::loaded=false;
map<int,string> Binding::names;


/** Creates a binding for a command with no argument. */
Binding::Binding(const Combo &combo, int command) {
	
	this->combo = combo;
	this->command = command;
	hasArg = false;
}


/** Creates a binding for a command with a floating-point argument. */
Binding::Binding(const Combo &combo, int command, float argument) {
	
	this->combo = combo;
	this->command = command;
	this->argf = argument;
	this->argi = NULL;
	hasArg = true;
}


/** Creates a binding for a command with an unsigned integer argument. */
Binding::Binding(const Combo &combo, int command, GLuint *argument) {
	
	this->combo = combo;
	this->command = command;
	this->argf = 0.0;
	this->argi = argument;
	hasArg = true;
}


/** Returns the value of the binding's argument. */
float Binding::getArgument() const {
	
	// Return value of argument
	if (argi != NULL)
		return static_cast<float>(*argi);
	else
		return argf;
}


/** @return String comprised of the modifier and string */
string Binding::toString() const {
	
	ostringstream stream;
	map<int,string>::const_iterator it;
	
	// Load
	if (!loaded) {
		load();
		loaded = true;
	}
	
	// Modifier
	switch (combo.modifier) {
	case CANVAS_MOD_CONTROL : stream << "Ctrl+"; break;
	case CANVAS_MOD_ALT     : stream << "Alt+"; break;
	case CANVAS_MOD_SHIFT   : stream << "Shift+"; break;
	}
	
	// Trigger
	it = names.find(combo.trigger);
	if (it != names.end()) {
		stream << it->second;
	} else if (isprint(combo.trigger)) {
		stream << combo.trigger;
	}
	
	// Command
	stream << " '" << Command::getName(command) << "'";
	
	// Finish
	return stream.str();
}


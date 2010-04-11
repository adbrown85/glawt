/*
 * Binding.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <iostream>
#include "Binding.hpp"
bool Binding::loaded=false;
map<int,string> Binding::triggerNames;




/**
 * Creates a keyboard binding for a command with no argument.
 * 
 * @param trigger
 *     Key pressed by user.
 * @param modifier
 *     Modifier key held while pressing trigger.  0 if none.
 * @param command
 *     Enumeration of a command.
 */
Binding::Binding(int trigger,
                 int modifier,
                 int command) {
	
	// Initialize using no state and no argument
	init(trigger, modifier, command, -1);
}



/**
 * Creates a keyboard binding for a command with an argument.
 * 
 * @param trigger
 *     Key pressed by user.
 * @param modifier
 *     Modifier key held while pressing trigger.  0 if none.
 * @param command
 *     Enumeration of a command.
 * @param argument
 *     Floating-point number to pass to the command as an argument.
 */
Binding::Binding(int trigger,
                 int modifier,
                 int command,
                 float argument) {
	
	// Initialize using no state and an argument
	init(trigger, modifier, command, -1, argument);
}



/**
 * Creates a mouse binding for a command with no argument.
 * 
 * @param trigger
 *     Button pressed by user.
 * @param modifier
 *     Modifier key held while pressing trigger.  0 if none.
 * @param command
 *     Enumeration of a command.
 * @param state
 *     State of the button pressed.  -1 if none.
 */
Binding::Binding(int trigger,
                 int modifier,
                 int command,
                 int state) {
	
	// Initialize using a state and no argument
	init(trigger, modifier, command, state);
}



/**
 * Creates a mouse binding for a command with a floating-point argument.
 * 
 * @param trigger
 *     Button pressed by user.
 * @param modifier
 *     Modifier key held while pressing trigger.  0 if none.
 * @param command
 *     Enumeration of a command.
 * @param argument
 *     Floating-point number to pass to the command as an argument.
 * @param state
 *     State of the button pressed.  -1 if none.
 */
Binding::Binding(int trigger,
                 int modifier,
                 int command,
                 float argument,
                 int state) {
	
	// Initialize using a state and an argument
	init(trigger, modifier, command, state, argument);
}



/**
 * Creates a mouse binding for a command with an unsigned integer argument.
 * 
 * @param trigger
 *     Button pressed by user.
 * @param modifier
 *     Modifier key held while pressing trigger.  0 if none.
 * @param command
 *     Enumeration of a command.
 * @param argument
 *     Pointer to an unsigned integer to pass to the command as an argument.
 * @param state
 *     State of the button pressed.  -1 if none.
 */
Binding::Binding(int trigger,
                 int modifier,
                 int command,
                 unsigned int *argument,
                 int state) {
	
	// Initialize using a state and an argument
	init(trigger, modifier, command, state, argument);
}



/**
 * Returns the value of the binding's argument.  If the argument holds a 
 * pointer to a variable, the pointer is first dereferenced.
 */
float Binding::getArgument() const {
	
	// Return value of argument
	if (argi != NULL)
		return static_cast<float>(*argi);
	else
		return argf;
}



/**
 * Returns a printable version of the modifier.
 */
string Binding::getModifierStr() const {
	
	string str="";
	
	// Lookup and return name
	switch (modifier) {
		case 0                 : str = "None"; break;
		case GLUT_ACTIVE_CTRL  : str = "Ctrl"; break;
		case GLUT_ACTIVE_ALT   : str = "Alt"; break;
		case GLUT_ACTIVE_SHIFT : str = "Shift"; break;
	}
	return str;
}



/**
 * Returns the name of a key or binding.
 */
string Binding::getTriggerStr() const {
	
	map<int,string>::const_iterator n;
	string str;
	
	// Lookup and return name
	if (isCharacter() && isalpha((char)trigger))
		str = trigger;
	else {
		n = triggerNames.find(trigger);
		if (n != triggerNames.end())
			str = n->second;
		else
			str = "-";
	}
	return str;
}



/**
 * Determines if this Binding should be used for when the mouse is dragged.  
 * Does so by checking if state is equal to 'x' or 'y'.
 */
bool Binding::hasDrag() const {
	
	return (state == 'x' || state == 'y');
}



/**
 * Initializes the required attributes for a binding.
 * 
 * @param trigger
 *     Key or button pressed by user.
 * @param modifier
 *     Modifier key held while pressing trigger.  0 if none.
 * @param command
 *     Enumeration of a command.
 * @param state
 *     State of the button pressed.  -1 if none.
 */
void Binding::init(int trigger,
                   int modifier,
                   int command,
                   int state) {
	
	// Load names if this is the first call
	if (!loaded)
		initTriggerNames();
	loaded = true;
	
	// Set standard attributes
	this->trigger = isCharacter(trigger) ? toupper(trigger) : trigger;
	this->modifier = modifier;
	this->command = command;
	this->state = state;
	hasArg = false;
}



/**
 * Initializes the required attributes for a binding.
 * 
 * @param trigger
 *     Key or button pressed by user.
 * @param modifier
 *     Modifier key held while pressing trigger.  0 if none.
 * @param command
 *     Enumeration of a command.
 * @param state
 *     State of the button pressed.  -1 if none.
 * @param argument
 *     Floating-point number to pass to the command as an argument.
 */
void Binding::init(int trigger,
                   int modifier,
                   int command,
                   int state,
                   float argument) {
	
	// Set standard attributes
	init(trigger, modifier, command, state);
	
	// Set argument
	this->argf = argument;
	this->argi = NULL;
	hasArg = true;
}



/**
 * Initializes the required attributes for a binding.
 * 
 * @param trigger
 *     Key or button pressed by user.
 * @param modifier
 *     Modifier key held while pressing trigger.  0 if none.
 * @param command
 *     Enumeration of a command.
 * @param state
 *     State of the button pressed.  -1 if none.
 * @param argument
 *     Pointer to an unsigned integer to pass to the command as an argument.
 */
void Binding::init(int trigger,
                   int modifier,
                   int command,
                   int state,
                   unsigned int *argument) {
	
	// Set standard attributes
	init(trigger, modifier, command, state);
	
	// Set argument
	this->argf = 0.0;
	this->argi = argument;
	hasArg = true;
}



/**
 * Initializes the formatted names of triggers.
 */
void Binding::initTriggerNames() {
	
	triggerNames[GLUT_KEY_LEFT] = "Left";
	triggerNames[GLUT_KEY_RIGHT] = "Right";
	triggerNames[GLUT_KEY_UP] = "Up";
	triggerNames[GLUT_KEY_DOWN] = "Down";
	triggerNames[GLUT_LEFT_BUTTON] = "Left";
	triggerNames[GLUT_MIDDLE_BUTTON] = "Middle";
	triggerNames[GLUT_RIGHT_BUTTON] = "Right";
	triggerNames[GLUT_UP_BUTTON] = "Wheel Up";
	triggerNames[GLUT_DOWN_BUTTON] = "Wheel Down";
	triggerNames['\t'] = "Tab";
	triggerNames[GLUT_KEY_HOME] = "Home";
	triggerNames[GLUT_KEY_END] = "End";
	triggerNames[GLUT_KEY_INSERT] = "Insert";
}



/**
 * Determines if the trigger should be printed as is as a character, or should 
 * be replaced with a formatted name.
 * 
 * @return
 *     True if trigger is not in the 'triggerNames' map.
 */
bool Binding::isCharacter(int trigger) {
	
	map<int,string>::const_iterator ni;
	
	// Check if in trigger names
	ni = triggerNames.find(trigger);
	return ni == triggerNames.end();
}



/**
 * Prints the binding.
 */
std::ostream& operator<<(std::ostream& stream,
                         const Binding &b) {
	
	string str;
	
	// Get formatted modifier and trigger
	if (b.hasModifier())
		str = b.getModifierStr() + "+";
	str += b.getTriggerStr();
	
	// Print with formatted command
	stream << std::setw(15) << std::left << str;
	stream << b.getCommandStr();
	return stream;
}

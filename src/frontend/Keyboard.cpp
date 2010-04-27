/*
 * Keyboard.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Keyboard.hpp"
Keyboard *Keyboard::obj=NULL;


Keyboard::Keyboard(Delegate *delegate,
                   Scene *scene) : 
                   Control(delegate, scene) {
	
	Keyboard::obj = this;
	type = "Keyboard";
	initBindings();
}


/**
 * Installs the controls into the current context.
 */
void Keyboard::install() {
	
	// Register callbacks
	glutKeyboardFunc(Keyboard::character);
	glutSpecialFunc(Keyboard::special);
}


/**
 * Handles character keys.
 */
void Keyboard::character(unsigned char key,
                         int x,
                         int y) {
	
	obj->trigger(static_cast<int>(toupper(key)));
}


/**
 * Looks up a Binding by its keyboard key and modifier.
 * 
 * Needed because the map is a multimap with keys being keyboard keys, and 
 * multiple keyboard keys can be included if the modifiers are considered.  
 * Gets the range of bindings that have the key, then searches through them for 
 * the one that has a matching modifier.
 * 
 * @param key Keyboard key.
 * @param modifier Modifier key.
 */
Binding* Keyboard::lookup(int key,
                          int modifier) {
	
	Binding *binding=NULL;
	multimap<int,Binding>::iterator bi;
	pair<multimap<int,Binding>::iterator,
	     multimap<int,Binding>::iterator> range;
	
	// Look through range
	range = bindings.equal_range(key);
	for (bi=range.first; bi!=range.second; ++bi) {
		binding = &bi->second;
		if (binding->getModifier() == modifier)
			return binding;
	}
	return NULL;
}


/**
 * Handles special keys.
 */
void Keyboard::special(int key,
                       int x,
                       int y) {
	
	obj->trigger(key);
}


/**
 * Triggers a command.
 */
void Keyboard::trigger(int key) {
	
	Binding *binding;
	int modifier;
	
	// Lookup command by key and modifier
	modifier = glutGetModifiers();
	if (modifier == 1 || modifier == 5)
		modifier -= 1;
	binding = lookup(key, modifier);
	if (binding == NULL)
		return;
	
	// Run command with argument if it has one
	if (binding->hasArgument())
		delegate->run(binding->getCommand(), binding->getArgument());
	else
		delegate->run(binding->getCommand());
	glutPostRedisplay();
}


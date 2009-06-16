/*
 * Keyboard.cpp
 *     Keyboard control for a 3D display.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Keyboard.hpp"
Keyboard *Keyboard::obj=NULL;



/**
 * Installs the controls into the current context.
 */
void Keyboard::install() {
	
	// Set up bindings
	bindings();
	print();
	
	// Register functions
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
 * Looks up a Binding by its keyboard key and modifier.  Needed because the map 
 * is a multimap with keys being keyboard keys, and multiple keyboard keys can 
 * be included if the modifiers are considered.  Gets the range of bindings 
 * that have the key, then searches through them for the one that has a 
 * matching modifier.
 * 
 * @param key
 *     Keyboard key.
 * @param mod
 *     Modifier.
 */
Binding* Keyboard::lookup(int key,
                          int mod) {
	
	Binding *bin=NULL;
	std::multimap<int,Binding>::iterator bi;
	pair<multimap<int,Binding>::iterator,
	     multimap<int,Binding>::iterator> ran;
	
	// Look through range
	ran = bins.equal_range(key);
	for (bi=ran.first; bi!=ran.second; ++bi) {
		bin = &bi->second;
		if (bin->getModifier() == mod)
			return bin;
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
	
	Binding *bin;
	int mod;
	
	// Lookup command by key and modifier
	mod = glutGetModifiers();
	if (mod == 1 || mod == 5)
		mod -= 1;
	bin = lookup(key, mod);
	if (bin == NULL)
		return;
	
	// Run command with argument if it has one
	if (bin->hasArgument())
		del->run(bin->getCommand(), bin->getArgument());
	else
		del->run(bin->getCommand());
	glutPostRedisplay();
}

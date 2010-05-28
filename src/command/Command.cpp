/*
 * Command.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Command.hpp"
map<int,string> Command::names;
bool Command::loaded=false;


/** Initializes the command names. */
void Command::initialize() {
	
	// Set names
	setNames();
	
	// Only initialize once
	loaded = true;
}


/** Prints the names of all the command names. */
void Command::print() {
	
	map<int,string>::iterator it;
	
	// Check if names not generated
	if (!loaded)
		initialize();
	
	// Print names
	for (it=names.begin(); it!=names.end(); it++)
		cout << it->first << " " << it->second << endl;
}


/** @return human-readable name of the command. */
string Command::getName(int command) {
	
	// Return name
	if (!loaded)
		initialize();
	return names[command];
}


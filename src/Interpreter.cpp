/*
 * Interpreter.cpp
 *     Interprets directives and issues commands for Gander.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Interpreter.hpp"



/**
 * Creates an Interpreter and initializes the commands.
 */
Interpreter::Interpreter() {
	
	// Initialize
	initialize();
}



/**
 * Initializes the commands.
 */
void Interpreter::initialize() {
	
	// Set descriptions
	des[GANDER_BOB] = "Bob";
	des[GANDER_CANCEL] = "Cancel";
	des[GANDER_CIRCLE] = "Circle";
	des[GANDER_CLOSE] = "Close";
	des[GANDER_COPY] = "Copy";
	des[GANDER_DELETE] = "Delete";
	des[GANDER_DESELECT] = "Deselect";
	des[GANDER_DESELECT_ALL] = "Deselect All";
	des[GANDER_DUPLICATE] = "Duplicate";
	des[GANDER_FIT] = "Fit";
	des[GANDER_FIT_ALL] = "Fit All";
	des[GANDER_GRAB] = "Grab";
	des[GANDER_HIDE] = "Hide";
	des[GANDER_INFORMATION] = "Information";
	des[GANDER_NUDGE] = "Nudge";
	des[GANDER_OVERLAY] = "Overlay";
	des[GANDER_PASTE] = "Paste";
	des[GANDER_PICK] = "Pick";
	des[GANDER_ROTATE] = "Rotate";
	des[GANDER_REVERT] = "Revert";
	des[GANDER_SCALE] = "Scale";
	des[GANDER_SAVE] = "Save";
	des[GANDER_SELECT_ALL] = "Select All";
	des[GANDER_TILT] = "Tilt";
	des[GANDER_UNHIDE] = "Unhide";
	des[GANDER_WEAVE] = "Weave";
	des[GANDER_ZOOM] = "Zoom";
	
	// Set commands
	
}



/**
 * Prints the commands.
 */
void Interpreter::print() {
	
	map<int, string>::iterator it;
	
	// Print
	cout << "Commands:" << endl;
	for (it=des.begin(); it!=des.end(); it++)
		cout << "  " << it->first << " " << it->second << endl;
}





/**
 * Simple test program.
 */
int main(int argc, char *argv[]) {
	
	Interpreter inter;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Interpreter" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	inter.print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Interpreter" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

/*
 * Command.cpp
 *     Class containing commands and a list of their names.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Command.hpp"
std::map<int,std::string> Command::names;
bool Command::loaded=false;




void Command::initialize() {
	
	// Only initialize once
	loaded = true;
	
	// Set names
	names[BOB_DOWN] = "Bob Down";
	names[BOB_UP] = "Bob Up";
	names[CIRCLE_LEFT] = "Circle Left";
	names[CIRCLE_RIGHT] = "Circle Right";
	names[FIT_SELECTED] = "Fit Selected";
	names[FIT_ALL] = "Fit All";
	names[TILT_DOWN] = "Tilt Down";
	names[TILT_UP] = "Tilt Up";
	names[WEAVE_LEFT] = "Weave Left";
	names[WEAVE_RIGHT] = "Weave Right";
	names[ZOOM_IN] = "Zoom In";
	names[ZOOM_OUT] = "Zoom Out";
	names[ROTATE_X_MINUS] = "Rotate X-";
	names[ROTATE_X_PLUS] = "Rotate X+";
	names[ROTATE_Y_MINUS] = "Rotate Y-";
	names[ROTATE_Y_PLUS] = "Rotate Y+";
	names[ROTATE_Z_MINUS] = "Rotate Z-";
	names[ROTATE_Z_PLUS] = "Rotate Z+";
	names[SCALE_X_MINUS] = "Scale X-";
	names[SCALE_X_PLUS] = "Scale X+";
	names[SCALE_Y_MINUS] = "Scale Y-";
	names[SCALE_Y_PLUS] = "Scale Y+";
	names[SCALE_Z_MINUS] = "Scale Z-";
	names[SCALE_Z_PLUS] = "Scale Z+";
	names[TRANSLATE_X_MINUS] = "Translate X-";
	names[TRANSLATE_X_PLUS] = "Translate X+";
	names[TRANSLATE_Y_MINUS] = "Translate Y-";
	names[TRANSLATE_Y_PLUS] = "Translate Y+";
	names[TRANSLATE_Z_MINUS] = "Translate Z-";
	names[TRANSLATE_Z_PLUS] = "Translate Z+";
	names[COPY] = "Copy";
	names[CUT] = "Cut";
	names[PASTE] = "Paste";
	names[EXIT] = "Exit";
	names[OPEN] = "Open";
	names[SAVE] = "Save";
	names[HIDE] = "Hide";
	names[SHOW_ALL] = "Show All";
	names[INFORMATION] = "Information";
	names[DESELECT] = "Deselect";
	names[GRAB] = "Grab";
	names[NEXT] = "Next";
	names[PREVIOUS] = "Previous";
	names[SELECT_ALL] = "Select All";
}



void Command::print() {
	
	using namespace std;
	map<int,string>::iterator it;
	
	// Check if names not generated
	if (!loaded)
		initialize();
	
	// Print names
	for (it=names.begin(); it!=names.end(); it++)
		cout << it->first << " " << it->second << endl;
}




/**
 * Simple test program.
 */
int main(int argc, char *argv[]) {
	
	using namespace std;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Command" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	Command::print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Command" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

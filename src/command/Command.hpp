/*
 * Command.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "common.h"
#include "Scene.hpp"
#include "Canvas.hpp"
using namespace std;


/** @brief %Commands passed to work with the %Scene.
 * @ingroup command
 */
class Command {
public:
	static void print();
	static string getName(int command);
	enum {
		BOOM, BOOM_DOWN, BOOM_UP,
		CIRCLE_X, CIRCLE_Y, CIRCLE_LEFT, CIRCLE_RIGHT, CIRCLE_DOWN, CIRCLE_UP,
		FIT_SELECTED, FIT_ALL,
		TRACK, TRACK_LEFT, TRACK_RIGHT,
		ZOOM_IN, ZOOM_OUT,
		RESET,
		ROTATE, ROTATE_X, ROTATE_Y, ROTATE_Z,
		SCALE, SCALE_X, SCALE_Y, SCALE_Z,
		TRANSLATE, TRANSLATE_X, TRANSLATE_Y, TRANSLATE_Z,
		COPY, CUT, PASTE, DUPLICATE,
		OPEN, LIST, SAVE, EXIT,
		HIDE, SHOW_ALL,
		INFORMATION,
		GRAB, DESELECT, SELECT_ALL,
		NEXT, PREVIOUS,
		MANIPULATE
	};
private :
	static bool loaded;
	static map<int,string> names;
	static void initialize();
	static void setNames();
};

/** Assigns human-readable names to the commands. */
inline void Command::setNames() {
	
	names[BOOM] = "Boom Camera";
	names[BOOM_DOWN] = "Boom Camera";
	names[BOOM_UP] = "Boom Camera";
	names[CIRCLE_Y] = "Pan Camera";
	names[CIRCLE_X] = "Tilt Camera";
	names[CIRCLE_LEFT] = "Pan Camera";
	names[CIRCLE_RIGHT] = "Pan Camera";
	names[CIRCLE_DOWN] = "Tilt Camera";
	names[CIRCLE_UP] = "Tilt Camera";
	names[FIT_SELECTED] = "Fit Selected";
	names[FIT_ALL] = "Fit All";
	names[TRACK] = "Track Camera";
	names[TRACK_LEFT] = "Track Camera";
	names[TRACK_RIGHT] = "Track Camera";
	names[ZOOM_IN] = "Zoom In";
	names[ZOOM_OUT] = "Zoom Out";
	names[RESET] = "Reset Camera";
	names[ROTATE] = "Rotate";
	names[ROTATE_X] = "Rotate X";
	names[ROTATE_Y] = "Rotate Y";
	names[ROTATE_Z] = "Rotate Z";
	names[SCALE] = "Scale";
	names[SCALE_X] = "Scale X";
	names[SCALE_Y] = "Scale Y";
	names[SCALE_Z] = "Scale Z";
	names[TRANSLATE] = "Translate";
	names[TRANSLATE_X] = "Translate X";
	names[TRANSLATE_Y] = "Translate Y";
	names[TRANSLATE_Z] = "Translate Z";
	names[COPY] = "Copy";
	names[CUT] = "Cut";
	names[PASTE] = "Paste";
	names[DUPLICATE] = "Duplicate";
	names[EXIT] = "Quit";
	names[OPEN] = "Open";
	names[LIST] = "List";
	names[SAVE] = "Save";
	names[HIDE] = "Hide";
	names[SHOW_ALL] = "Show All";
	names[INFORMATION] = "Information";
	names[DESELECT] = "Deselect All";
	names[GRAB] = "Select/Deselect Item";
	names[NEXT] = "Next";
	names[PREVIOUS] = "Previous";
	names[SELECT_ALL] = "Select All";
	names[MANIPULATE] = "Use Manipulator";
}

#endif

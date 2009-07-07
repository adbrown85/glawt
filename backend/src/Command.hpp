/*
 * Command.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __COMMAND_HEADER__
#define __COMMAND_HEADER__
#include <iostream>
#include <map>
#include <string>
using std::cout;
using std::endl;
using std::map;
using std::string;



/**
 * @brief
 *     Commands passed to Delegates to change the Scene or Items.
 */
class Command {
	
	
	public:
		
		static void print();
		static string getName(int command);
		
		enum {
			BOOM,
			BOOM_DOWN,
			BOOM_UP,
			CIRCLE_X,
			CIRCLE_Y,
			CIRCLE_LEFT,
			CIRCLE_RIGHT,
			CIRCLE_DOWN,
			CIRCLE_UP,
			FIT_SELECTED,
			FIT_ALL,
			TRACK,
			TRACK_LEFT,
			TRACK_RIGHT,
			ZOOM_IN,
			ZOOM_OUT,
			RESET,
			ROTATE_X_MINUS,
			ROTATE_X_PLUS,
			ROTATE_Y_MINUS,
			ROTATE_Y_PLUS,
			ROTATE_Z_MINUS,
			ROTATE_Z_PLUS,
			SCALE_X_MINUS,
			SCALE_X_PLUS,
			SCALE_Y_MINUS,
			SCALE_Y_PLUS,
			SCALE_Z_MINUS,
			SCALE_Z_PLUS,
			TRANSLATE_X_MINUS,
			TRANSLATE_X_PLUS,
			TRANSLATE_Y_MINUS,
			TRANSLATE_Y_PLUS,
			TRANSLATE_Z_MINUS,
			TRANSLATE_Z_PLUS,
			COPY,
			CUT,
			PASTE,
			DUPLICATE,
			EXIT,
			OPEN,
			SAVE,
			HIDE,
			SHOW_ALL,
			INFORMATION,
			DESELECT,
			GRAB,
			NEXT,
			PREVIOUS,
			SELECT_ALL,
			MANIPULATE
		};
	
	
	private :
		
		static void initialize();
		
		static bool loaded;
		static map<int,string> names;
		
		static void setNames() {
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
			names[DUPLICATE] = "Duplicate";
			names[EXIT] = "Quit";
			names[OPEN] = "Open";
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
};


#endif

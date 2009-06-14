/*
 * Command.hpp
 *     Class containing commands and a list of their names.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __GANDER_COMMAND_HEADER__
#define __GANDER_COMMAND_HEADER__
#include <iostream>
#include <map>
#include <string>



class Command {
	
	
	public:
		
		static std::map<int,std::string> names;
		
		static void initialize();
		static void print();
		
		enum {
			BOB_DOWN,
			BOB_UP,
			CIRCLE_LEFT,
			CIRCLE_RIGHT,
			FIT_SELECTED,
			FIT_ALL,
			TILT_DOWN,
			TILT_UP,
			WEAVE_LEFT,
			WEAVE_RIGHT,
			ZOOM_IN,
			ZOOM_OUT,
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
			SELECT_ALL
		};
	
	
	private :
		
		static bool loaded;
};


#endif

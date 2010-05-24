/*
 * Command.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef COMMAND_HPP
#define COMMAND_HPP
#include <iostream>
#include <map>
#include <string>
#include "Scene.hpp"
#include "Canvas.hpp"
using namespace std;


/**
 * @ingroup backend
 * @brief %Commands passed to work with the %Scene.
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


/* Function pointer for a command with no arguments. */
typedef void(*handler_0)(Scene*,Canvas*,int);

/* Function pointer for a command with a float argument. */
typedef void(*handler_f)(Scene*,Canvas*,int,float);

/* Function pointer for a command with a string argument. */
typedef void(*handler_s)(Scene*,Canvas*,int,const string&);


/**
 * @interface Delegate
 * @ingroup backend
 * @brief Interface for a worker that performs %Commands on the %Scene.
 * 
 * @see Cameraman
 * @see Compositor
 * @see Director
 * @see Grip
 * @see Interpreter
 * @see Producer
 */
class Delegate {
public:
	map<int,handler_0> getHandlersZero();
	map<int,handler_f> getHandlersFloat();
	map<int,handler_s> getHandlersString();
	string getType() const;
protected:
	Canvas *canvas;
	Scene *scene;
	string type;
	map<int,handler_0> handlersZero;
	map<int,handler_f> handlersFloat;
	map<int,handler_s> handlersString;
};

/** @return All the zero-argument handlers this delegate contains. */
inline map<int,handler_0> Delegate::getHandlersZero() {return handlersZero;}

/** @return All the float-argument handlers this delegate contains. */
inline map<int,handler_f> Delegate::getHandlersFloat() {return handlersFloat;}

/** @return All the string-argument handlers this delegate contains. */
inline map<int,handler_s> Delegate::getHandlersString() {return handlersString;}

/** @return Name of the delegate. */
inline string Delegate::getType() const {return type;}


#endif

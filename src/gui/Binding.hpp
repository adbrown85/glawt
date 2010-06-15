/*
 * Binding.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BINDING_HPP
#define BINDING_HPP
#include "common.h"
#include <iomanip>
#include "Command.hpp"
#include "Canvas.hpp"
using namespace std;


/** @brief Maps a combination of keys or buttons to a command.
 * @ingroup gui
 */
class Binding {
public:
	Binding(const Combo &combo, int command);
	Binding(const Combo &combo, int command, float arg);
	Binding(const Combo &combo, int command, GLuint *arg);
	float getArgument() const;
	Combo& getCombo();
	int getCommand() const;
	bool hasArgument() const;
	string toString() const;
protected:
	static void load();
	static map<int,string> names;
	static bool loaded;
private:
	bool hasArg;
	Combo combo;
	int command;
	unsigned int *argi;
	float argf;
};

inline Combo& Binding::getCombo() {return combo;}
inline int Binding::getCommand() const {return command;}
inline bool Binding::hasArgument() const {return hasArg;}

/** Initializes the formatted names of triggers. */
inline void Binding::load() {
	
	names[CANVAS_MINUS] = "-";
	names[CANVAS_PLUS] = "+";
	names[CANVAS_EQUALS] = "=";
	names[CANVAS_ESCAPE] = "Esc";
	names[CANVAS_KEY_LEFT] = "Left";
	names[CANVAS_KEY_RIGHT] = "Right";
	names[CANVAS_KEY_UP] = "Up";
	names[CANVAS_KEY_DOWN] = "Down";
	names[CANVAS_LEFT_BUTTON] = "LMB";
	names[CANVAS_MIDDLE_BUTTON] = "MMB";
	names[CANVAS_RIGHT_BUTTON] = "RMB";
	names[CANVAS_WHEEL_UP] = "MWU";
	names[CANVAS_WHEEL_DOWN] = "MWD";
}





#endif

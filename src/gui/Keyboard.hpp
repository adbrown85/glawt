/*
 * Keyboard.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include "common.h"
#include <cctype>                       // Check if triggers are printable
#include "Control.hpp"
#include "Scene.hpp"
using namespace std;


/** @brief %Keyboard control for a canvas.
 * @ingroup gui
 */
class Keyboard : public Control, public CanvasListener {
public:
	Keyboard(Delegate *delegate);
	virtual void install();
	virtual void onCanvasEvent(const CanvasEvent &event);
protected:
	void addBindings();
};

/** Adds all the default keyboard bindings. */
inline void Keyboard::addBindings() {
	
	Combo combo;
	
	// Left arrow
	combo.trigger = CANVAS_KEY_LEFT;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_DOWN;
	add(Binding(combo, Command::CIRCLE_LEFT, 5.0f));
	
	// Right arrow
	combo.trigger = CANVAS_KEY_RIGHT;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_DOWN;
	add(Binding(combo, Command::CIRCLE_RIGHT, 5.0f));
	
	// Down arrow
	combo.trigger = CANVAS_KEY_DOWN;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_DOWN;
	add(Binding(combo, Command::CIRCLE_DOWN, 5.0f));
	
	// Up arrow
	combo.trigger = CANVAS_KEY_UP;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_DOWN;
	add(Binding(combo, Command::CIRCLE_UP, 5.0f));
	
	// Escape
	combo.trigger = CANVAS_ESCAPE;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_DOWN;
	add(Binding(combo, Command::EXIT));
	
	// Ctrl + q
	combo.trigger = 'q';
	combo.modifier = CANVAS_MOD_CONTROL;
	combo.action = CANVAS_DOWN;
	add(Binding(combo, Command::EXIT));
	
	// Minus
	combo.trigger = CANVAS_MINUS;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_DOWN;
	add(Binding(combo, Command::ZOOM_OUT, 1.0f));
	
	// Plus
	combo.trigger = CANVAS_EQUALS;
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_DOWN;
	add(Binding(combo, Command::ZOOM_IN, +1.0f));
	
	// a
	combo.trigger = 'a';
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_DOWN;
	add(Binding(combo, Command::SELECT_ALL));
	
	// d
	combo.trigger = 'd';
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_DOWN;
	add(Binding(combo, Command::DESELECT));
	
	// h
	combo.trigger = 'h';
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_DOWN;
	add(Binding(combo, Command::HIDE));
	
	// v
	combo.trigger = 'v';
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_DOWN;
	add(Binding(combo, Command::SHOW_ALL));
	
	// i
	combo.trigger = 'i';
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_DOWN;
	add(Binding(combo, Command::INFORMATION));
	
	// t
	combo.trigger = 't';
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_DOWN;
	add(Binding(combo, Command::TRANSLATE));
	
	// s
	combo.trigger = 's';
	combo.modifier = CANVAS_MOD_NONE;
	combo.action = CANVAS_DOWN;
	add(Binding(combo, Command::SCALE));
	
	//add(Binding('Q', CANVAS_MOD_CONTROL, Command::EXIT));
	//add(Binding(CANVAS_KEY_HOME, 0, Command::RESET));
	// add(Binding('C', GLUT_ACTIVE_ALT, Command::COPY));
	// add(Binding('V', GLUT_ACTIVE_ALT, Command::PASTE));
	// add(Binding('X', GLUT_ACTIVE_ALT, Command::CUT));
	// add(Binding('S', GLUT_ACTIVE_ALT, Command::SAVE));
	// add(Binding('W', GLUT_ACTIVE_ALT, Command::EXIT));
	// add(Binding('D', GLUT_ACTIVE_ALT, Command::DUPLICATE));
	// add(Binding('F', 0, Command::FIT_SELECTED));
	// add(Binding('A', 0, Command::FIT_ALL));
	// add(Binding('\t', 0, Command::NEXT));
}


#endif

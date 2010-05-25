/*
 * Keyboard.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <utility>
#include <vector>
#include <GL/glut.h>
#include "Control.hpp"
#include "Scene.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief %Keyboard control for the %Display.
 */
class Keyboard : public Control {
public:
	Keyboard(Interpreter *interpreter);
	static void character(int key, int x, int y);
	static void special(int key, int x, int y);
	virtual void install();
	Binding* lookup(int key, int mod);
	void trigger(int key);
protected:
	void initBindings();
private:
	static Keyboard *obj;
};

/** Adds all the default keyboard bindings to Gander. */
inline void Keyboard::initBindings() {
	
	add(Binding(CANVAS_KEY_LEFT, 0, Command::CIRCLE_LEFT, 5.0f));
	add(Binding(CANVAS_KEY_RIGHT, 0, Command::CIRCLE_RIGHT, 5.0f));
	add(Binding(CANVAS_KEY_DOWN, 0, Command::CIRCLE_DOWN, 5.0f));
	add(Binding(CANVAS_KEY_UP, 0, Command::CIRCLE_UP, 5.0f));
	//add(Binding(CANVAS_KEY_HOME, 0, Command::RESET));
	add(Binding(CANVAS_ESCAPE, 0, Command::EXIT));
	//add(Binding('Q', CANVAS_MOD_CONTROL, Command::EXIT));
	add(Binding('q', CANVAS_MOD_CONTROL, Command::EXIT));
	add(Binding(CANVAS_MINUS, 0, Command::ZOOM_OUT, 1.0f));
	add(Binding(CANVAS_EQUALS, 0, Command::ZOOM_IN, +1.0f));
	add(Binding('a', 0, Command::SELECT_ALL));
	add(Binding('d', 0, Command::DESELECT));
	add(Binding('h', 0, Command::HIDE));
	add(Binding('v', 0, Command::SHOW_ALL));
	add(Binding('i', 0, Command::INFORMATION));
	add(Binding('t', 0, Command::TRANSLATE));
	add(Binding('s', 0, Command::SCALE));
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

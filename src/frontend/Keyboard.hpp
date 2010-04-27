/*
 * Keyboard.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include <cctype>
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include "Binding.hpp"
#include "Command.hpp"
#include "Control.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief
 *     %Keyboard control for the %Display.
 */
class Keyboard : public Control {
	
	public:
		
		Keyboard(Delegate *delegate,
		         Scene *scene);
		static void character(unsigned char key, int x, int y);
		static void special(int key, int x, int y);
		virtual void install();
		Binding* lookup(int key, int mod);
		void trigger(int key);
		
	
	protected:
		
		void initBindings();
	
	private:
		
		static Keyboard *obj;
};


inline void Keyboard::initBindings() {
	
	add(Binding(GLUT_KEY_LEFT, 0, Command::CIRCLE_LEFT, 5.0f));
	add(Binding(GLUT_KEY_RIGHT, 0, Command::CIRCLE_RIGHT, 5.0f));
	add(Binding(GLUT_KEY_DOWN, 0, Command::CIRCLE_DOWN, 5.0f));
	add(Binding(GLUT_KEY_UP, 0, Command::CIRCLE_UP, 5.0f));
	add(Binding(GLUT_KEY_HOME, 0, Command::RESET));
	add(Binding('Q', GLUT_ACTIVE_ALT, Command::EXIT));
	add(Binding('A', 0, Command::SELECT_ALL));
	add(Binding('D', 0, Command::DESELECT));
	add(Binding('H', 0, Command::HIDE));
	add(Binding('S', 0, Command::SHOW_ALL));
	add(Binding('I', 0, Command::INFORMATION));
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

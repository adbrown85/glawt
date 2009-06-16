/*
 * Keyboard.hpp
 *     Keyboard control for a 3D display.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __KEYBOARD_HEADER__
#define __KEYBOARD_HEADER__
#include <cctype>
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <map>
#include <utility>
#include "Binding.hpp"
#include "Command.hpp"
#include "Control.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"
#include "State.hpp"



class Keyboard : public Control {
	
	
	private :
		
		std::multimap<int,Binding> bins;
		
		static Keyboard *obj;
		
		void add(const Binding &bin) {
			bins.insert(pair<int,Binding>(bin.getTrigger(), bin));
		}
		void bindings() {
			add(Binding(GLUT_KEY_LEFT, Command::CIRCLE_LEFT, 5.0f));
			add(Binding(GLUT_KEY_RIGHT, Command::CIRCLE_RIGHT, 5.0f));
			add(Binding(GLUT_KEY_DOWN, Command::CIRCLE_DOWN, 5.0f));
			add(Binding(GLUT_KEY_UP, Command::CIRCLE_UP, 5.0f));
			add(Binding(GLUT_KEY_HOME, Command::RESET));
			add(Binding('c', Command::COPY, GLUT_ACTIVE_ALT));
			add(Binding('v', Command::PASTE, GLUT_ACTIVE_ALT));
			add(Binding('x', Command::CUT, GLUT_ACTIVE_ALT));
			add(Binding('s', Command::SAVE, GLUT_ACTIVE_ALT));
			add(Binding('q', Command::EXIT, GLUT_ACTIVE_ALT));
			add(Binding('w', Command::EXIT, GLUT_ACTIVE_ALT));
			add(Binding('a', Command::SELECT_ALL, GLUT_ACTIVE_ALT));
			add(Binding('d', Command::DESELECT));
			add(Binding('d', Command::DUPLICATE, GLUT_ACTIVE_ALT));
			add(Binding('f', Command::FIT_SELECTED));
			add(Binding('a', Command::FIT_ALL));
			add(Binding('\t', Command::NEXT));
			add(Binding('i', Command::INFORMATION));
			add(Binding('h', Command::HIDE));
			add(Binding('u', Command::SHOW_ALL));
		}
	
	
	public :
		
		Keyboard() {Keyboard::obj = this;}
		
		void install();
		Binding* lookup(int key, int mod);
		void trigger(int key);
		
		static void character(unsigned char key, int x, int y);
		static void special(int key, int x, int y);
		
		void print() {
			std::multimap<int,Binding>::iterator bi;
			for (bi=bins.begin(); bi!=bins.end(); bi++)
				std::cout << "  " << bi->second << std::endl;
		}
};


#endif

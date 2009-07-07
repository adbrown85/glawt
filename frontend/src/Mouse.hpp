/*
 * Mouse.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __MOUSE_HEADER__
#define __MOUSE_HEADER__
#include <cmath>
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <map>
#include <typeinfo>
#include <utility>
#include "Binding.hpp"
#include "Command.hpp"
#include "Control.hpp"
#include "Delegate.hpp"
#include "Manipulator.hpp"
#include "Picker.hpp"
#include "Scene.hpp"
#include "Translator.hpp"
#include "Vector.hpp"
using std::map;
using std::multimap;
using std::pair;
using std::vector;



/**
 * @brief
 *     %Mouse control for the %Display.
 * @ingroup frontend
 * 
 * @todo
 *     Need to deallocate manipulators.
 */
class Mouse : public Control {
	
	
	public :
		
		Mouse(Delegate *delegate) : Control(delegate) {}
		
		void handleDrag(int x, int y);
		void handleClick(int button, int action, int x, int y);
		vector<Manipulator*> install(Scene *scene);
		
		static void motion(int x, int y);
		static void mouse(int button, int action, int x, int y);
	
	
	private :
		
		int currentItemID, dragCount;
		Manipulator *currentManipulator;
		map<char,Binding*> dragBindings;
		Vector dragAxis, dragDirection, lastCursorPosition;
		
		static Mouse *obj;
		
		void installBindings() {
			add(Binding(GLUT_UP_BUTTON, 0, Command::ZOOM_IN, 1.0f, GLUT_DOWN));
			add(Binding(GLUT_DOWN_BUTTON, 0, Command::ZOOM_OUT, 1.0f, GLUT_DOWN));
			add(Binding(GLUT_LEFT_BUTTON, GLUT_ACTIVE_ALT, Command::GRAB, &currentItemID, GLUT_DOWN));
			add(Binding(GLUT_LEFT_BUTTON, 0, Command::CIRCLE_Y, -1.0f, 'x', Binding::EXCLUSIVE));
			add(Binding(GLUT_LEFT_BUTTON, 0, Command::CIRCLE_X, -1.0f, 'y', Binding::EXCLUSIVE));
			add(Binding(GLUT_MIDDLE_BUTTON, 0, Command::TRACK, -1.0f, 'x'));
			add(Binding(GLUT_MIDDLE_BUTTON, 0, Command::BOOM, 1.0f, 'y'));
			add(Binding(GLUT_LEFT_BUTTON, GLUT_ACTIVE_ALT, Command::MANIPULATE, GLUT_DOWN));
		}
		void installCallbacks() {
			glutMouseFunc(Mouse::mouse);
			glutMotionFunc(Mouse::motion);
		}
		void installManipulators() {
			add(new Translator(1.0, 0.0, 0.0));
			add(new Translator(0.0, 1.0, 0.0));
			add(new Translator(0.0, 0.0, 1.0));
		}
};


#endif

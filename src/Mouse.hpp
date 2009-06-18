/*
 * Mouse.hpp
 *     Mouse control for a 3D display.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __MOUSE_HEADER__
#define __MOUSE_HEADER__
#include <algorithm>
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <set>
#include "Command.hpp"
#include "Control.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"
#include "State.hpp"
using std::multimap;
using std::set;



class Mouse : public Control {
	
	
	private :
		
		bool dragX, dragY;
		float dragXArg, dragYArg;
		int dragXCmd, dragYCmd, xLast, yLast;
		
		static Mouse *obj;
		static set<int> spcs;
		
		void specials() {
			spcs.insert(Command::GRAB);
		}
		void bindings() {
			add(Binding(GLUT_UP_BUTTON, 0, Command::ZOOM_OUT, 1.0f, GLUT_DOWN));
			add(Binding(GLUT_DOWN_BUTTON, 0, Command::ZOOM_IN, 1.0f, GLUT_DOWN));
			add(Binding(GLUT_LEFT_BUTTON, GLUT_ACTIVE_ALT, Command::GRAB, GLUT_DOWN));
			add(Binding(GLUT_LEFT_BUTTON, 0, Command::CIRCLE_Y, -1.0f, Binding::DRAG_X));
			add(Binding(GLUT_LEFT_BUTTON, 0, Command::CIRCLE_X, -1.0f, Binding::DRAG_Y));
			add(Binding(GLUT_MIDDLE_BUTTON, 0, Command::TRACK, -1.0f, Binding::DRAG_X));
			add(Binding(GLUT_MIDDLE_BUTTON, 0, Command::BOOM, 1.0f, Binding::DRAG_Y));
		}
	
	
	public :
		
		Mouse() {
			dragX = false;
			dragY = false;
		};
		
		void install();
		static void motion(int x,
		                   int y);
		static void mouse(int button,
		                  int action,
		                  int x,
		                  int y);
		static bool needsCoordinates(int cmd);
};


#endif

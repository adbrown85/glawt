/*
 * Mouse.hpp
 *     Mouse control for a 3D display.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __MOUSE_HEADER__
#define __MOUSE_HEADER__
#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include "Command.hpp"
#include "Control.hpp"
#include "Delegate.hpp"
#include "Scene.hpp"
#include "State.hpp"



class Mouse : public Control {
	
	
	private :
		
		bool allowRotate, allowTrans;
		int xLast, yLast;
		
		static Mouse *instance;
	
	
	public :
		
		Mouse() :
		      allowRotate(false),
		      allowTrans(false) {};
		
		void install();
		static void motion(int x,
		                   int y);
		static void mouse(int button,
		                  int action,
		                  int x,
		                  int y);
};


#endif

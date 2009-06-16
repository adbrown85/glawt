/*
 * Display.hpp
 *     3D display for items.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef __DISPLAY_HEADER__
#define __DISPLAY_HEADER__
#define DISPLAY_DEFAULT_X 100
#define DISPLAY_DEFAULT_Y 100
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include "Control.hpp"
#include "Interpreter.hpp"
#include "Item.hpp"
#include "Outline.hpp"
#include "Scene.hpp"
#include "State.hpp"



class Display {
	
	
	public :
		
		static void display(void);
		static void install(Control *control);
		static void start(std::string title,
		                  Scene *scene,
		                  State *state);
	
	
	private :
		
		static Outline outline;
		static Scene *scene;
		static State *state;
		static Interpreter *interp;
		static std::vector<Control*> cons;
		
		static void overlay();
};


#endif

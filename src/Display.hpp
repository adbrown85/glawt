/*
 * Display.hpp
 *     3D display for items.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__
#define DISPLAY_DEFAULT_X 100
#define DISPLAY_DEFAULT_Y 100
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include "Controls.hpp"
#include "Item.hpp"
#include "Menu.hpp"
#include "Scene.hpp"



class Display {
	
	
	public :
		
		static void display(void);
		static void start(std::string title,
		                  Scene *scene);
	
	
	private :
		
		static Scene *scene;
		
		static void overlay();
};


#endif

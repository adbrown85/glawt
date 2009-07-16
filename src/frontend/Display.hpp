/*
 * Display.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__
#define DISPLAY_DEFAULT_X 100
#define DISPLAY_DEFAULT_Y 100
#include <cstdlib>
#include <GL/glut.h>
#include <iomanip>
#include <iostream>
#include <vector>
#include "Control.hpp"             // Install controls before starting
#include "Manipulator.hpp"         // Draw UI widgets for controls
#include "Scene.hpp"               // Pass root node to Painter
#include "Painter.hpp"             // Paints the screen with scene
using std::string;
using std::vector;



/**
 * @brief
 *     3D display for items in a scene.
 * @ingroup frontend
 */
class Display {
	
	
	public :
		
		static void display(void);
		static void install(Control *control);
		static void start(string title,
		                  Scene *scene);
	
	
	private :
		
		static Scene *scene;
		static vector<Control*> controls;
		static vector<Manipulator*> manipulators;
		
		static void overlay();
};


#endif

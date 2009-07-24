/*
 * Display.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iomanip>
#include <iostream>
#include <vector>
#include "Command.hpp"             // Open the scene
#include "Control.hpp"             // Install controls before starting
#include "Delegate.hpp"            // Open the scene
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
		                  Scene *scene,
		                  Delegate *delegate);
	
	
	private :
		
		static Scene *scene;
		static Delegate *delegate;
		static vector<Control*> controls;
		static vector<Manipulator*> manipulators;
		
		static void overlay();
};


#endif

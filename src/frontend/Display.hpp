/*
 * Display.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
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
using namespace std;


/**
 * @brief
 *     3D display for items in a scene.
 * @ingroup frontend
 */
class Display {
	
	public :
		
		static void display(void);
		static void idle(void);
		static void install(Control *control);
		static void start(int argc,
		                  char *argv[],
		                  string title,
		                  Scene *scene,
		                  Delegate *delegate);
		static void visibility(int visible);
	
	private :
		
		static Delegate *delegate;
		static unsigned long timeStarted;
		static int frames, framesPerSecond;
		static Scene *scene;
		static vector<Control*> controls;
		static vector<Manipulator*> manipulators;
		
		static void overlay();
};


#endif

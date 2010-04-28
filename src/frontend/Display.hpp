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
#include <string>
#include <vector>
#include "Command.hpp"             // Open the scene
#include "Control.hpp"             // Install controls before starting
#include "Interpreter.hpp"         // Send commands
#include "Manipulator.hpp"         // Draw UI widgets for controls
#include "Scene.hpp"               // Pass root node to Painter
#include "Painter.hpp"             // Paints the screen with scene
using namespace std;


/**
 * @ingroup frontend
 * @brief
 *     3D display for items in a scene.
 */
class Display {
	
	public :
		
		Display(Scene *scene,
		        Interpreter *interpreter);
		static void display(void);
		static void idle(void);
		void install(Control *control);
		void start(int argc,
		           char *argv[],
		           const string &title);
		static void toggleOverlay();
	
	private :
		
		static Display *obj;
		bool useOverlay;
		Interpreter *interpreter;
		unsigned long timeStarted;
		int frames, framesPerSecond;
		Painter *painter;
		Scene *scene;
		vector<Control*> controls;
		
		void overlay();
		static void checkError();
};


#endif

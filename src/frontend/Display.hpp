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
#include "Window.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief
 *     3D display for items in a scene.
 */
class Display {
	
	public:
		
		Display(Scene *scene,
		        const string &title);
		static void display(void);
		Interpreter* getInterpreter();
		static void idle(void);
		static void init(int argc,
		                 char *argv[]);
		void install(Control *control);
		void start();
		static void toggleOverlay();
	
	protected:
		
		void overlay();
	
	private:
		
		static Display *obj;
		bool useOverlay;
		Interpreter interpreter;
		unsigned long timeStarted;
		int frames, framesPerSecond;
		Painter *painter;
		Scene *scene;
		vector<Control*> controls;
};


inline Interpreter* Display::getInterpreter() {
	
	return &interpreter;
}


#endif

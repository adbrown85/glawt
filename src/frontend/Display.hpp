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
#define DEFAULT_WINDOW_X 100
#define DEFAULT_WINDOW_Y 100
using namespace std;


/**
 * @ingroup frontend
 * @brief
 *     3D display for items in a scene.
 */
class Display {
	
	public:
		
		Display(Scene *scene,
		        const string &title,
		        int argc,
		        char *argv[]);
		static void display(void);
		Interpreter* getInterpreter();
		static void idle(void);
		void install(Control *control);
		void start();
		static void toggleOverlay();
	
	protected:
		
		static void checkError();
		void overlay();
	
	private:
		
		static Display *obj;
		bool useOverlay;
		Interpreter interpreter;
		unsigned long timeStarted;
		int frames, framesPerSecond, width, height;
		Painter *painter;
		Scene *scene;
		string title;
		vector<Control*> controls;
};


inline Interpreter* Display::getInterpreter() {
	
	return &interpreter;
}


#endif

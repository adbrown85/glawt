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
#include <sstream>
#include <string>
#include <vector>
#include "Exception.hpp"
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
 * @brief 3D display for items in a scene.
 */
class Display {
public:
	Display(Interpreter *interpreter);
	void add(Control *control);
	void computeFootprint();
	static void display(void);
	Interpreter* getInterpreter();
	static void idle(void);
	static void toggleOverlay(int command);
protected:
	void overlay();
private:
	static Display *obj;
	bool useOverlay;
	Interpreter *interpreter;
	unsigned long timeStarted;
	int frames, framesPerSecond;
	Painter *painter;
	vector<Control*> controls;
	double footprint;
};


inline Interpreter* Display::getInterpreter() {return interpreter;}


#endif

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
#include "Delegate.hpp"         // Send commands
#include "Manipulator.hpp"         // Draw UI widgets for controls
#include "Scene.hpp"               // Pass root node to Painter
#include "Painter.hpp"             // Paints the screen with scene
#include "Canvas.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief 3D display for items in a scene.
 */
class Display : public CommandListener {
public:
	Display(Delegate *delegate);
	void add(Control *control);
	void computeFootprint();
	static void display(void);
	Delegate* getDelegate();
	static void idle(void);
	virtual void onCommandEvent(int command);
	static void toggleOverlay();
protected:
	void overlay();
private:
	static Display *obj;
	bool useOverlay;
	Delegate *delegate;
	unsigned long timeStarted;
	int frames, framesPerSecond;
	Painter *painter;
	vector<Control*> controls;
	double footprint;
	Canvas *canvas;
};

inline Delegate* Display::getDelegate() {return delegate;}


#endif

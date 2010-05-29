/*
 * Display.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include "common.h"
#include <iomanip>
#include <vector>
#include <glibmm/timer.h>
#include "Exception.hpp"
#include "Command.hpp"             // Open the scene
#include "Control.hpp"             // Install controls before starting
#include "Delegate.hpp"            // Send commands
#include "Manipulator.hpp"         // Draw UI widgets for controls
#include "Scene.hpp"               // Pass root node to Painter
#include "Painter.hpp"             // Paints the screen with scene
#include "Canvas.hpp"
using namespace std;


/** @brief 3D display for items in a scene.
 * @ingroup gui
 */
class Display : public CanvasListener, CommandListener {
public:
	Display(Delegate *delegate);
	void add(Control *control);
	void computeFootprint();
	virtual void onCanvasEvent(const CanvasEvent &event);
	Delegate* getDelegate();
	virtual void onCommandEvent(int command);
	void toggleOverlay();
protected:
	void overlay();
private:
	bool useOverlay;
	Delegate *delegate;
	unsigned long timeStarted;
	int frames, framesPerSecond;
	Painter *painter;
	vector<Control*> controls;
	double footprint;
	Canvas *canvas;
	Glib::Timer timer;
};

inline Delegate* Display::getDelegate() {return delegate;}


#endif

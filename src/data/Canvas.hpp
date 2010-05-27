/*
 * Canvas.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CANVAS_HPP
#define CANVAS_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Log.hpp"
#include "Camera.hpp"
#define CANVAS_WIDTH 512
#define CANVAS_HEIGHT 512
#define CANVAS_DOWN 1
#define CANVAS_UP 0
#define CANVAS_NONE -1
#define CANVAS_LEFT_BUTTON 1
#define CANVAS_MIDDLE_BUTTON 2
#define CANVAS_RIGHT_BUTTON 3
#define CANVAS_WHEEL_DOWN 4
#define CANVAS_WHEEL_UP 5
using namespace std;


/* Button or key with modifier and if trigger is up or down. */
struct Combo {
	int trigger, modifier, action;
};

/* Current mouse coordinates and combination. */
struct CanvasState {
	int x, y;
	Combo combo;
};

/* Change in the state of the canvas and what caused it. */
#define CANVAS_EVENT_TYPE_SIZE 6
class Canvas;
struct CanvasEvent {
	enum {SETUP,DISPLAY,KEY,BUTTON,DRAG,IDLE};
	int type;
	Canvas *source;
	CanvasState state;
};

/* Object that wants to be informed of changes in the canvas. */
class CanvasListener {
public:
	virtual void onCanvasEvent(const CanvasEvent &event) = 0;
}; 


/** Area in a window that can be drawn to. */
class Canvas {
public:
	Canvas(int width=CANVAS_WIDTH, int height=CANVAS_HEIGHT);
	void addListener(CanvasListener *listener, int type);
	void clear();
	void check();
	void fireEvent(int type);
	virtual void flush() = 0;
	Camera* getCamera();
	Vector getSize();
	virtual void refresh() = 0;
protected:
	bool isMouseButtonPressed;
	CanvasState state;
private:
	int height, width;
	Camera camera;
	list<CanvasListener*> listeners[CANVAS_EVENT_TYPE_SIZE];
};

/** Wipes the canvas clean. */
inline void Canvas::clear() {glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);}

/** @return Pointer to the canvas's camera. */
inline Camera* Canvas::getCamera() {return &camera;}

/** @return Width and height of the canvas. */
inline Vector Canvas::getSize() {return Vector(width,height);}


#endif

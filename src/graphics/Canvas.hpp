/*
 * Canvas.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CANVAS_HPP
#define CANVAS_HPP
#include "common.h"
#include <algorithm>                    // For find
#include <GL/glu.h>
#include "Log.hpp"
#include "Camera.hpp"
#include "Combo.hpp"
#include "Extensions.hpp"
#define CANVAS_WIDTH 512
#define CANVAS_HEIGHT 512
#define CANVAS_DOWN 1
#define CANVAS_UP 0
#define CANVAS_NONE -1
#ifdef HAVE_GTK
#include <gdk/gdkkeysyms.h>
#define CANVAS_LEFT_BUTTON 1
#define CANVAS_MIDDLE_BUTTON 2
#define CANVAS_RIGHT_BUTTON 3
#define CANVAS_WHEEL_DOWN 4
#define CANVAS_WHEEL_UP 5
#define CANVAS_KEY_UP GDK_Up
#define CANVAS_KEY_DOWN GDK_Down
#define CANVAS_KEY_LEFT GDK_Left
#define CANVAS_KEY_RIGHT GDK_Right
#define CANVAS_MINUS GDK_minus
#define CANVAS_PLUS GDK_plus
#define CANVAS_EQUALS GDK_equal
#define CANVAS_ESCAPE GDK_Escape
#define CANVAS_MOD_CONTROL GDK_Control_L
#define CANVAS_MOD_ALT GDK_Alt_L
#define CANVAS_MOD_SHIFT GDK_Shift_L
#define CANVAS_MOD_NONE 0
#endif
#ifdef HAVE_GLUT
#include <GL/glut.h>
#define CANVAS_LEFT_BUTTON 0
#define CANVAS_MIDDLE_BUTTON 1
#define CANVAS_RIGHT_BUTTON 2
#define CANVAS_WHEEL_UP 3
#define CANVAS_WHEEL_DOWN 4
#define CANVAS_KEY_UP 128
#define CANVAS_KEY_DOWN 129
#define CANVAS_KEY_LEFT 130
#define CANVAS_KEY_RIGHT 131
#define CANVAS_MINUS '-'
#define CANVAS_PLUS '+'
#define CANVAS_EQUALS '='
#define CANVAS_ESCAPE 27
#define CANVAS_MOD_CONTROL GLUT_ACTIVE_CTRL
#define CANVAS_MOD_ALT GLUT_ACTIVE_ALT
#define CANVAS_MOD_SHIFT GLUT_ACTIVE_SHIFT
#define CANVAS_MOD_NONE 0
#endif
using namespace std;


/* Current mouse coordinates and combination. */
struct CanvasState {
	int x, y;
	Combo combo;
};

/* Change in the state of the canvas and what caused it. */
#define CANVAS_EVENT_TYPE_SIZE 5
class Canvas;
struct CanvasEvent {
	enum {SETUP,DISPLAY,KEY,BUTTON,DRAG};
	int type;
	Canvas *source;
	CanvasState state;
};

/* Object that wants to be informed of changes in the canvas. */
class CanvasListener {
public:
	virtual void onCanvasEvent(const CanvasEvent &event) = 0;
}; 


/** @brief Area in a window that can be drawn to.
 * @ingroup graphics
 */
class Canvas {
public:
	Canvas(int width=CANVAS_WIDTH, int height=CANVAS_HEIGHT);
	void addListener(CanvasListener *listener, int type);
	void clear();
	void check();
	void fireEvent(int type);
	virtual void flush() = 0;
	Camera* getCamera();
	int getHeight();
	int getWidth();
	virtual void refresh() = 0;
	virtual void primeStart() = 0;
	virtual void primeFinish() = 0;
	virtual void setAutomaticallyRefresh(bool automaticRefresh) = 0;
	virtual void write(const string &text, int x=15, int y=30) = 0;
protected:
	bool automaticallyRefresh, started;
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

/** @return Height of the canvas. */
inline int Canvas::getHeight() {return height;}

/** @return Width of the canvas. */
inline int Canvas::getWidth() {return width;}


#endif

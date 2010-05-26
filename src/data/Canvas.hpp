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
#include <gtkmm.h>
#include <gtkglmm.h>
#include "Matrix.hpp"
#include "Quaternion.hpp"
#include "Vector.hpp"
#include "Log.hpp"
#define CANVAS_WIDTH 512
#define CANVAS_HEIGHT 512
#define CANVAS_ZOOM -10.0
#define CANVAS_ROTATE_AMOUNT 5.0
#define CANVAS_DOWN 1
#define CANVAS_UP 0
#define CANVAS_NONE -1
#define CANVAS_LEFT_BUTTON 1
#define CANVAS_MIDDLE_BUTTON 2
#define CANVAS_RIGHT_BUTTON 3
#define CANVAS_WHEEL_DOWN 4
#define CANVAS_WHEEL_UP 5
#define CANVAS_KEY_UP GDK_Up
#define CANVAS_KEY_DOWN GDK_Down
#define CANVAS_KEY_LEFT GDK_Left
#define CANVAS_KEY_RIGHT GDK_Right
#define CANVAS_R GDK_R
#define CANVAS_r GDK_r
#define CANVAS_Q GDK_Q
#define CANVAS_q GDK_q
#define CANVAS_MINUS GDK_minus
#define CANVAS_PLUS GDK_plus
#define CANVAS_EQUALS GDK_equal
#define CANVAS_ESCAPE GDK_Escape
#define CANVAS_MOD_CONTROL GDK_Control_L
#define CANVAS_MOD_ALT GDK_Alt_L
#define CANVAS_MOD_SHIFT GDK_Shift_L
using namespace std;
//using System::log;


/* Callback definitions */
typedef void (*display_cb_t)(void);
typedef void (*drag_cb_t)(int,int);
typedef void (*keyboard_cb_t)(int,int,int);
typedef void (*idle_cb_t)(void);
typedef void (*mouse_cb_t)(int,int,int,int);
typedef void (*special_cb_t)(int,int,int);
typedef void (*setup_cb_t)();


/** Area in a window that can be drawn to. */
class Canvas : public Gtk::GL::DrawingArea {
public:
	Canvas(int width=CANVAS_WIDTH, int height=CANVAS_HEIGHT);
	void applyView();
	void begin();
	void clear();
	void check();
	void end();
	void flush();
	int getWidth();
	int getHeight();
	int getModifier();
	Vector getPosition() const ;
	Matrix getRotationMatrix() const;
	static void init(int argc, char *argv[]);
	virtual bool on_expose_event(GdkEventExpose *event);
	virtual void on_realize();
	virtual bool on_button_press_event(GdkEventButton *event);
	virtual bool on_button_release_event(GdkEventButton *event);
	virtual bool on_key_press_event(GdkEventKey *event);
	virtual bool on_motion_notify_event(GdkEventMotion *event);
	virtual bool on_scroll_event(GdkEventScroll *event);
	void refresh();
	void reset();
	void rotate(float angle, const Vector &axis);
	void setDisplayCallback(display_cb_t display);
	void setDragCallback(drag_cb_t drag);
	void setKeyboardCallback(keyboard_cb_t keyboard);
	void setMouseCallback(mouse_cb_t mouse);
	void setSetupCallback(setup_cb_t setup);
	void translate(const Vector &move);
	void translate(float x, float y, float z);
protected:
	void updateModifer(guint state);
private:
	bool mouseButtonPressed;
	int height, width;
	int lastMouseMotionEventTime, lastMouseX, lastMouseY;
	int mouseButton, mouseWheel;
	int modifier;
	Gdk::GL::ConfigMode mode;
	Glib::RefPtr<Gdk::GL::Context> glContext;
	Glib::RefPtr<Gdk::GL::Config> glConfig;
	Glib::RefPtr<Gdk::GL::Drawable> glDrawable;
	Glib::RefPtr<Gdk::GL::Window> glWindow;
	Glib::RefPtr<Gdk::Window> window;
	display_cb_t display;
	drag_cb_t drag;
	keyboard_cb_t keyboard;
	mouse_cb_t mouse;
	setup_cb_t setup;
	Quaternion rotation;
	Vector position;
};

/** Signal start of OpenGL commands. */
inline void Canvas::begin() {glDrawable->gl_begin(glContext);}

/** Signal end of OpenGL commands. */
inline void Canvas::end() {glDrawable->gl_end();}

/** Resets all the pixels in the canvas. */
inline void Canvas::clear() {glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);}

/** Forces the canvas to push all the pixels to the screen. */
inline void Canvas::flush() {glWindow->swap_buffers();}

/** @return Width of the canvas. */
inline int Canvas::getWidth() {return width;}

inline int Canvas::getModifier() {return modifier;}

/** @return Height of the canvas. */
inline int Canvas::getHeight() {return height;}

/** @return Position of the camera. */
inline Vector Canvas::getPosition() const {return position;}

/** Forces the canvas to be redrawn. */
inline void Canvas::refresh() {window->invalidate_rect(get_allocation(), 0);}

/** Assigns function to be called to draw the canvas. */
inline void Canvas::setDisplayCallback(display_cb_t d) {display = d;}

/** Assigns function to be called when mouse is dragged. */
inline void Canvas::setDragCallback(drag_cb_t d) {drag = d;}

/** Assigns function to be called when mouse button is pressed or released. */
inline void Canvas::setKeyboardCallback(keyboard_cb_t k) {keyboard = k;}

/** Assigns function to be called when mouse button is pressed or released. */
inline void Canvas::setMouseCallback(mouse_cb_t m) {mouse = m;}

/** Assigns function to be called for initialization. */
inline void Canvas::setSetupCallback(setup_cb_t s) {setup = s;}

/** Moves the camera. */
inline void Canvas::translate(float x,float y,float z) {translate(Vector(x,y,z));}

/** @return Rotation of the camera as a matrix. */
inline Matrix Canvas::getRotationMatrix() const {return rotation.getMatrix();}


#endif

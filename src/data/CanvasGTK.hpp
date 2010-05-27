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
#include <glibmm/refptr.h>
#include <gdkmm/window.h>
#include <gdk/gdkkeysyms.h>
#include <gtkmm/gl/init.h>
#include <gtkmm/gl/drawingarea.h>
#include "Canvas.hpp"
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
using namespace std;


/** Area in a window that can be drawn to using GTK GL. */
class CanvasGTK : public Canvas,
                  public Gtk::GL::DrawingArea {
public:
	CanvasGTK(int width=CANVAS_WIDTH, int height=CANVAS_HEIGHT);
	virtual void flush();
	virtual bool on_expose_event(GdkEventExpose *event);
	virtual void on_realize();
	virtual bool on_button_press_event(GdkEventButton *event);
	virtual bool on_button_release_event(GdkEventButton *event);
	virtual bool on_key_press_event(GdkEventKey *event);
	virtual bool on_motion_notify_event(GdkEventMotion *event);
	virtual bool on_scroll_event(GdkEventScroll *event);
	virtual void refresh();
protected:
	void begin();
	void end();
	void updateModifer(guint state);
private:
	Gdk::GL::ConfigMode mode;
	Glib::RefPtr<Gdk::GL::Context> glContext;
	Glib::RefPtr<Gdk::GL::Config> glConfig;
	Glib::RefPtr<Gdk::GL::Drawable> glDrawable;
	Glib::RefPtr<Gdk::GL::Window> glWindow;
	Glib::RefPtr<Gdk::Window> window;
};

/** Signal start of OpenGL commands. */
inline void Canvas::begin() {glDrawable->gl_begin(glContext);}

/** Signal end of OpenGL commands. */
inline void Canvas::end() {glDrawable->gl_end();}

/** Forces the canvas to push all the pixels to the screen. */
inline void Canvas::flush() {glWindow->swap_buffers();}


#endif

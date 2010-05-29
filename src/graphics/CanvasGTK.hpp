/*
 * CanvasGTK.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CANVASGTK_HPP
#define CANVASGTK_HPP
#include "common.h"
#include <GL/glu.h>
#include <glibmm/refptr.h>
#include <gdkmm/window.h>
#include <gtkmm/gl/init.h>
#include <gtkmm/gl/drawingarea.h>
#include "Canvas.hpp"
#include "Typeface.hpp"
using namespace std;
using System::glog;


/** @brief Area in a window that can be drawn to using GTK GL.
 * @ingroup graphics
 */
class CanvasGTK : public Canvas,
                  public Gtk::GL::DrawingArea {
public:
	CanvasGTK(int width=CANVAS_WIDTH, int height=CANVAS_HEIGHT);
	virtual void flush();
	virtual bool on_expose_event(GdkEventExpose *event);
	virtual void on_realize();
	virtual bool on_button_press_event(GdkEventButton *event);
	virtual bool on_button_release_event(GdkEventButton *event);
	virtual bool on_idle();
	virtual bool on_key_press_event(GdkEventKey *event);
	virtual bool on_map_event(GdkEventAny *event);
	virtual bool on_motion_notify_event(GdkEventMotion *event);
	virtual bool on_scroll_event(GdkEventScroll *event);
	virtual void refresh();
	virtual void setAutomaticallyRefresh(bool automaticallyRefresh);
	virtual void write(const string &text, int x=15, int y=30);
protected:
	void begin();
	void end();
	void connectIdle();
	void disconnectIdle();
	void updateModifer(guint state);
private:
	Gdk::GL::ConfigMode mode;
	Glib::RefPtr<Gdk::GL::Context> glContext;
	Glib::RefPtr<Gdk::GL::Config> glConfig;
	Glib::RefPtr<Gdk::GL::Drawable> glDrawable;
	Glib::RefPtr<Gdk::GL::Window> glWindow;
	Glib::RefPtr<Gdk::Window> window;
	Typeface typeface;
	sigc::connection idle;
};

/** Signal start of OpenGL commands. */
inline void CanvasGTK::begin() {glDrawable->gl_begin(glContext);}

/** Signal end of OpenGL commands. */
inline void CanvasGTK::end() {glDrawable->gl_end();}

/** Forces the canvas to push all the pixels to the screen. */
inline void CanvasGTK::flush() {glWindow->swap_buffers();}

/** Forces the canvas to be redrawn. */
inline void CanvasGTK::refresh() {window->invalidate_rect(get_allocation(),0);}




#endif

/*
 * WindowGTK.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WINDOWGTK_HPP
#define WINDOWGTK_HPP
#include "common.h"
#ifdef HAVE_GTK
#include <gtkmm/window.h>
#include <gtkmm/widget.h>
#include "Window.hpp"
#include "CanvasGTK.hpp"
using namespace std;


/** @brief Window implementation for GTK toolkit.
 * @ingroup graphics
 */
class WindowGTK : public Window {
public:
	WindowGTK();
	virtual ~WindowGTK();
	virtual Gtk::Window* getWindow();
	virtual void add(Gtk::Widget &widget);
	virtual void add(Canvas *canvas);
	virtual void run();
	virtual void setIcon(string filename);
	virtual void show();
private:
	Gtk::Window *window;
};

inline Gtk::Window* WindowGTK::getWindow() {return window;}


#endif // HAVE_GTK
#endif

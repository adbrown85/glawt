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
#include <gdkmm/window.h>
#include "Window.hpp"
using namespace std;


class WindowGTK : public Window {
public:
	WindowGTK();
	virtual ~WindowGTK();
	virtual void add(Gtk::Widget &widget);
	virtual void add(Canvas *canvas);
	virtual run();
	virtual void show();
private:
	Gtk::Window *window;
};


#endif // HAVE_GTK
#endif

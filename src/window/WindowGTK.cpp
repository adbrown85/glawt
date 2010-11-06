/*
 * WindowGTK.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "WindowGTK.hpp"
#ifdef HAVE_GTK


/** Create a GTK window. */
WindowGTK::WindowGTK() {
	
	window = new Gtk::Window();
}


/** Destroys the GTK window. */
WindowGTK::~WindowGTK() {
	
	delete window;
}


/** Adds a GTK widget to the window. */
void WindowGTK::add(Gtk::Widget &widget) {
	
	window->add(widget);
}


/** Adds the canvas to the window. */
void WindowGTK::add(Canvas *canvas) {
	
	window->add(*(dynamic_cast<CanvasGTK*>(canvas)));
}


void* WindowGTK::getNativeWindow() {
	
	return (void*)window;
}

/** Hides the window. */
void WindowGTK::hide() {
	
	window->hide();
}


/** Starts processing the window. */
void WindowGTK::run() {
	
	Gtk::Main::run(*window);
}


/** Sets the icon used for the window. */
void WindowGTK::setIcon(string filename) {
	
	window->set_icon_from_file(filename);
}


/** Makes the window visible on screen. */
void WindowGTK::show() {
	
	window->set_title(getTitle());
	window->show_all();
}


#endif // HAVE_GTK

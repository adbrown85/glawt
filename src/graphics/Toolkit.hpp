/*
 * Toolkit.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TOOLKIT_HPP
#define TOOLKIT_HPP
#include "common.h"
#ifdef HAVE_GTK
#include <gtkmm/main.h>
#include <gtkmm/gl/init.h>
#endif
#ifdef HAVE_GLUT
#include <GL/glut.h>
#endif
using namespace std;


/** @brief Abstraction for the windowing toolkit.
 * @ingroup graphics
 */
class Toolkit {
public:
	Toolkit(int argc, char *argv[]);
	~Toolkit();
private:
#ifdef HAVE_GTK
	Gtk::Main *kit;
#endif
};


#endif

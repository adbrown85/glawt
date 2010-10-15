/*
 * About.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef ABOUT_HPP
#define ABOUT_HPP
#include "common.h"
#ifdef HAVE_GTK
#include <gtkmm/aboutdialog.h>
#include "Resources.hpp"
using namespace std;


/** @brief Utility for showing the %About dialog.
 * @ingroup gui
 */
class About {
public:
	static void show(Gtk::Window *parent=NULL);
};


#endif // HAVE_GTK
#endif

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
#include <gdk/gdkkeysyms.h>
#define TOOLKIT_DOWN 1
#define TOOLKIT_UP 0
#define TOOLKIT_NONE -1
#define TOOLKIT_LEFT_BUTTON 1
#define TOOLKIT_MIDDLE_BUTTON 2
#define TOOLKIT_RIGHT_BUTTON 3
#define TOOLKIT_WHEEL_DOWN 4
#define TOOLKIT_WHEEL_UP 5
#define TOOLKIT_KEY_UP GDK_Up
#define TOOLKIT_KEY_DOWN GDK_Down
#define TOOLKIT_KEY_LEFT GDK_Left
#define TOOLKIT_KEY_RIGHT GDK_Right
#define TOOLKIT_MINUS GDK_minus
#define TOOLKIT_PLUS GDK_plus
#define TOOLKIT_EQUALS GDK_equal
#define TOOLKIT_ESCAPE GDK_Escape
#define TOOLKIT_MOD_CONTROL GDK_Control_L
#define TOOLKIT_MOD_ALT GDK_Alt_L
#define TOOLKIT_MOD_SHIFT GDK_Shift_L
#define TOOLKIT_MOD_NONE 0
#endif
#ifdef HAVE_GLUT
#include <GL/glut.h>
#define TOOLKIT_DOWN GLUT_DOWN
#define TOOLKIT_UP GLUT_UP
#define TOOLKIT_NONE -1
#define TOOLKIT_LEFT_BUTTON 0
#define TOOLKIT_MIDDLE_BUTTON 1
#define TOOLKIT_RIGHT_BUTTON 2
#define TOOLKIT_WHEEL_UP 3
#define TOOLKIT_WHEEL_DOWN 4
#define TOOLKIT_KEY_UP 128
#define TOOLKIT_KEY_DOWN 129
#define TOOLKIT_KEY_LEFT 130
#define TOOLKIT_KEY_RIGHT 131
#define TOOLKIT_MINUS '-'
#define TOOLKIT_PLUS '+'
#define TOOLKIT_EQUALS '='
#define TOOLKIT_ESCAPE 27
#define TOOLKIT_MOD_CONTROL GLUT_ACTIVE_CTRL
#define TOOLKIT_MOD_ALT GLUT_ACTIVE_ALT
#define TOOLKIT_MOD_SHIFT GLUT_ACTIVE_SHIFT
#define TOOLKIT_MOD_NONE 0
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

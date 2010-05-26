/*
 * LogBook.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef LOGBOOK_HPP
#define LOGBOOK_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <gtkmm.h>
using namespace std;
using Glib::RefPtr;


/** @brief Widget for displaying the log.
 * @ingroup frontend
 */
class LogBook : public Gtk::Frame {
public:
	LogBook();
private:
	RefPtr<Gtk::TextBuffer> buffer;
	Gtk::TextView view;
	Gtk::ScrolledWindow scroller;
};


#endif

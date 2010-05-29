/*
 * LogBook.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef LOGBOOK_HPP
#define LOGBOOK_HPP
#include "common.h"
#include <gtkmm.h>
#include "Log.hpp"
using namespace std;
using Glib::RefPtr;
using System::glog;


/** @brief Widget for displaying the log.
 * @ingroup gui
 */
class LogBook : public Gtk::Frame, public LogListener {
public:
	LogBook();
	virtual void onLogUpdate(const string &text);
private:
	RefPtr<Gtk::TextBuffer> buffer;
	Gtk::TextView view;
	Gtk::ScrolledWindow scroller;
};


#endif

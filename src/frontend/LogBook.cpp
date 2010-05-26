/*
 * LogBook.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "LogBook.hpp"


LogBook::LogBook() {
	
	// Set up text view
	view.property_cursor_visible() = false;
	buffer = view.get_buffer();
	buffer->set_text("Opened the LogBook!");
	
	// Set up scroller
	scroller.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scroller.set_size_request(512, 100);
	
	// Pack
	scroller.add(view);
	add(scroller);
	set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
	set_border_width(2);
}


/*
 * Typeface.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Typeface.hpp"
#ifdef HAVE_GTK


/** Generates enough display lists for each character. */
Typeface::Typeface() {
	
	base = glGenLists(128);
}


/** Load the font and create the display lists for each character. */
bool Typeface::load(const string &descriptor) {
	
	Pango::FontDescription description;
	Pango::FontMetrics metrics;
	
	// Load display lists from font
	description = Pango::FontDescription(descriptor);
	font = Gdk::GL::Font::use_pango_font(description, 0, 128, base);
	if (!font) {
		return false;
	}
	
	// Find the height
	metrics = font->get_metrics();
	height = PANGO_PIXELS(metrics.get_ascent() + metrics.get_descent());
	
	// Finish
	return true;
}


/** Write some text by calling the display lists. */
void Typeface::write(const string &text) {
	
	if (font) {
		glListBase(base);
		glCallLists(text.length(), GL_UNSIGNED_BYTE, text.c_str());
	}
}


#endif

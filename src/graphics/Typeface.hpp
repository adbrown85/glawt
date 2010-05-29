/*
 * Typeface.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TYPEFACE_HPP
#define TYPEFACE_HPP
#include "common.h"
#ifdef HAVE_GTK
#include <gdkmm/gl/font.h>
using namespace std;
using Glib::RefPtr;


/** @brief Utility for drawing text with GTK GL.
 * @ingroup graphics
 */
class Typeface {
public:
	Typeface();
	int getHeight() const;
	void load(const string &descriptor);
	void write(const string &text);
private:
	GLuint base;
	int height;
};

/** @return Number of pixels from descender to ascender. */
inline int Typeface::getHeight() const {return height;}


#endif
#endif

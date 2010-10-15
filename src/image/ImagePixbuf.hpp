/*
 * ImagePixbuf.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef IMAGEPIXBUF_HPP
#define IMAGEPIXBUF_HPP
#include "common.h"
#ifdef HAVE_PIXBUFS
#include <gdkmm/pixbuf.h>
#include "Image.hpp"
using namespace std;
using Glib::RefPtr;


/** @brief Image loaded from a pixbuf.
 * 
 * Uses a Gdk::Pixbuf to load the file.  Therefore PNG, JPG, and 
 * GIF, as well as a number of other images are supported.
 * 
 * @ingroup graphics
 */
class ImagePixbuf : public Image {
public:
	ImagePixbuf(const string &filename);
	virtual ~ImagePixbuf();
	virtual GLchar* getData() const;
protected:
	void unpack();
private:
	GLchar *data;
	RefPtr<Gdk::Pixbuf> pixbuf;
};

/** @return Pointer to the raw, unpacked pixel data. */
inline GLchar* ImagePixbuf::getData() const {return data;}


#endif // HAVE_PIXBUFS
#endif

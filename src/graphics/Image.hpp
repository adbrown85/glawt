/*
 * Image.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef IMAGE_HPP
#define IMAGE_HPP
#include "common.h"
#include <gdkmm/pixbuf.h>
#include "Exception.hpp"
using namespace std;
using Glib::RefPtr;


/** @brief Loads pixel data from a file.
 * 
 * Currently uses a Gdk::Pixbuf to load the file.  Therefore PNG, JPG, and 
 * GIF, as well as a number of other images are supported.
 * 
 * @ingroup graphics
 */
class Image {
public:
	Image(const string &filename);
	string getFilename() const;
	GLchar* getData() const;
	GLenum getFormat() const;
	int getWidth() const;
	int getHeight() const;
protected:
	void unpack();
private:
	string filename;
	GLenum format;
	int width, height;
	RefPtr<Gdk::Pixbuf> pixbuf;
	GLchar *data;
};

/** @return Name of the file the image was loaded from. */
inline string Image::getFilename() const {return filename;}

/** @return GL_RGB or GL_RGBA. */
inline GLenum Image::getFormat() const {return format;}

/** @return Pointer to the raw, unpacked pixel data. */
inline GLchar* Image::getData() const {return data;}

/** @return Size of the image in the X direction. */
inline int Image::getWidth() const {return width;}

/** @return Size of the image in the Y direction. */
inline int Image::getHeight() const {return height;}


#endif

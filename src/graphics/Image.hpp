/*
 * Image.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef IMAGE_HPP
#define IMAGE_HPP
#include "common.h"
#include "Exception.hpp"
using namespace std;


/** @brief Abstract class representing an image loaded from a file.
 * 
 * @ingroup graphics
 */
class Image {
public:
	Image(const string &filename);
	virtual ~Image() {}
	string getFilename() const;
	virtual GLchar* getData() const = 0;
	GLenum getFormat() const;
	int getWidth() const;
	int getHeight() const;
protected:
	void setFormat(GLenum format);
	void setHeight(int height);
	void setWidth(int width);
private:
	GLenum format;
	int width, height;
	string filename;
};

/** @return Name of the file the image was loaded from. */
inline string Image::getFilename() const {return filename;}

/** @return GL_RGB or GL_RGBA. */
inline GLenum Image::getFormat() const {return format;}

/** @return Size of the image in the X direction. */
inline int Image::getWidth() const {return width;}

/** @return Size of the image in the Y direction. */
inline int Image::getHeight() const {return height;}

inline void Image::setFormat(GLenum format) {this->format = format;}

inline void Image::setHeight(int height) {this->height = height;}

inline void Image::setWidth(int width) {this->width = width;}


#endif

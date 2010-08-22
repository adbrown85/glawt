/*
 * PixelFormat.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PIXELFORMAT_HPP
#define PIXELFORMAT_HPP
#include "common.h"
#include "Exception.hpp"
using namespace std;


/** @brief Utility for working with formats for textures and buffers.
 * @ingroup graphics
 */
class PixelFormat {
public:
	static GLenum getFormat(const string &format);
	static string getFormat(GLenum format);
protected:
	static void load();
	static void loadFormats();
private:
	static bool loaded;
	static map<string,GLenum> formats;
};


#endif

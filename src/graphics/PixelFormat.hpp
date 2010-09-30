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
	static GLenum getFormat(const string &name);
	static string getFormat(GLenum code);
protected: // Helpers
	static void addFormat(const string &name, GLenum code);
	static void load();
	static void loadNameConversions();
private:   // Data
	static bool loaded;
	static map<string,GLenum> namesToCodes;
	static map<GLenum,string> codesToNames;
};


#endif

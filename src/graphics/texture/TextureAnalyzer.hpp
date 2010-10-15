/*
 * TextureAnalyzer.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TEXTUREANALYZER_HPP
#define TEXTUREANALYZER_HPP
#include "common.h"
#include "Exception.hpp"
#include "Log.hpp"
#include "PixelFormat.hpp"
using namespace std;


/** @brief Utility for analyzing textures.
 * @ingroup graphics
 */
class TextureAnalyzer {
public:    // Accessors
	GLint getBitsPerPixel();
	GLint getBytesPerPixel();
	GLenum getFormat();
	GLint getFootprint();
	GLint getWidth();
	GLint getHeight();
	GLint getDepth();
	bool isCompressed();
public:    // Mutators
	void setTexture(GLenum type, GLuint handle);
protected:
	GLint getRedSize();
	GLint getGreenSize();
	GLint getBlueSize();
	GLint getAlphaSize();
	GLint getRGBSize();
	GLint getRGBASize();
	GLint getLuminanceSize();
	GLint getFootprintCompressed();
	GLint getFootprintRaw();
private:
	GLenum type;
	GLuint handle;
};


#endif

/*
 * TextureBuilder.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TEXTUREBUILDER_HPP
#define TEXTUREBUILDER_HPP
#include "common.h"
#include "PixelFormat.hpp"
#include "TextureAnalyzer.hpp"
using namespace std;


/* Details for a texture that will be created. */
struct TextureOrder {
	GLenum type;
	string format;
	int width, height, depth;
};

/* Details about a texture that was created. */
struct TextureInvoice {
	GLenum type;
	string format;
	GLint width, height, depth;
	GLuint handle;
	GLint footprint, precision;
};

/** @brief Base class for a builder that makes textures.
 * @ingroup graphics
 */
class TextureBuilder {
public:
	TextureInvoice build(const string &filename, bool compress=false);
	TextureInvoice build(const TextureOrder &order);
public:    // Accessors
	virtual GLenum getType() const = 0;
protected: // Helpers
	virtual void prepare();
	virtual void assemble(const string &filename) = 0;
	virtual void assemble(const TextureOrder &order) = 0;
	virtual void complete() = 0;
	virtual void package();
private:   // Data
	TextureInvoice invoice;
};


#endif

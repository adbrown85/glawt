/*
 * TextureFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TEXTUREFACTORY_HPP
#define TEXTUREFACTORY_HPP
#include "common.h"
#include "Path.hpp"
#include "TextureBuilder2D.hpp"
#include "TextureBuilder3D.hpp"
using namespace std;


/** @brief Creates textures for other objects.
 * 
 * Will load textures from files or create blank ones.
 * 
 * In the case of a texture loaded from a file, the factory will use the file 
 * extension in the name to determine all the necessary attributes.  In 
 * addition, if that file was already loaded, the same texture will be given 
 * back.
 * 
 * In the case of a blank texture, the requesting object should fill out an 
 * order for the texture using the TextureOrder structure.  The type field 
 * should be either GL_TEXTURE_1D or GL_TEXTURE_2D, and the format should be 
 * one of GL_RGB, GL_RGBA, or GL_RGBA16F.  Of course, the width and height 
 * fields need to be specified according to the type.
 * 
 * handle, 
 * 
 * @ingroup graphics
 */
class TextureFactory {
public:
	static TextureInvoice create(const string& filename, bool compress=false);
	static TextureInvoice create(const TextureOrder &order);
private:
	static map<string,TextureInvoice> inventory;
	static TextureBuilder2D builder2D;
	static TextureBuilder3D builder3D;
};


#endif

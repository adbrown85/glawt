/*
 * TextureBuilder2D.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TEXTUREBUILDER2D_HPP
#define TEXTUREBUILDER2D_HPP
#include "common.h"
#include "TextureBuilder.hpp"
#include "ImageFactory.hpp"
using namespace std;


/** @brief Builder for 2D textures.
 * @ingroup graphics
 */
class TextureBuilder2D : public TextureBuilder {
public:    // Accessors
	virtual GLenum getType() const;
protected: // Helpers
	virtual void assemble(const string &filename);
	virtual void assemble(const TextureOrder &order);
	virtual void complete();
};

/** @return Dimensionality of the texture. */
inline GLenum TextureBuilder2D::getType() const {return GL_TEXTURE_2D;}


#endif

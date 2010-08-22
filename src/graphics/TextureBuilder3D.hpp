/*
 * TextureBuilder3D.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TEXTUREBUILDER3D_HPP
#define TEXTUREBUILDER3D_HPP
#include "common.h"
#include "TextureBuilder.hpp"
#include "Dataset.hpp"
using namespace std;


/** @brief Builder for 3D textures.
 * @ingroup graphics
 */
class TextureBuilder3D : public TextureBuilder {
public:    // Accessors
	virtual GLenum getType() const;
protected: // Helpers
	virtual void assemble(const string &filename);
	virtual void assemble(const TextureOrder &order);
	virtual void complete();
};

/** @return Dimensionality of the texture. */
inline GLenum TextureBuilder3D::getType() const {return GL_TEXTURE_3D;}


#endif

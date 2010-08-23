/*
 * Texture.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include "common.h"
#include "Node.hpp"                     // Base class
#include "NodeInterfaces.hpp"
#include "Scout.hpp"
#include "TextureFactory.hpp"
using namespace std;


/** @brief OpenGL texture node.
 * 
 * Provides basic texture capability, including finding an open texture unit 
 * and binding the texture to that unit.
 * 
 * @ingroup basic
 */
class Texture : public Node,
                public Applicable, public Nameable {
public:
	Texture(const Tag &tag);
	virtual void check();
	virtual void associate();
	virtual void finalize();
	virtual void apply();
	virtual void remove() {}
	virtual string toString() const;
public:    // Accessors
	virtual string getFilename() const;
	virtual GLuint getFootprint() const;
	virtual GLuint getHandle() const;
	virtual GLint getSize() const;
	virtual GLenum getType() const;
	virtual GLuint getUnit() const;
	virtual bool hasFilename() const;
protected: // Helpers
	void activate() const;
	void bind() const;
	TextureOrder makeOrder() const;
private:
	GLenum type;
	GLuint handle, unit, footprint, precision;
	string filename, format;
	int size;
};

/** Activates the correct texture unit. */
inline void Texture::activate() const {glActiveTexture(GL_TEXTURE0 + unit);}

/** Binds the texture to the active texture unit. */
inline void Texture::bind() const {glBindTexture(type, handle);}

/** @return Path to the file this texture was loaded from. */
inline string Texture::getFilename() const {return filename;}

/** @return OpenGL's unique identifier for this texture. */
inline GLuint Texture::getHandle() const {return handle;}

/** @return Width of the texture. */
inline GLint Texture::getSize() const {return size;}

/** @return Number of bytes used to store the texture. */
inline GLuint Texture::getFootprint() const {return footprint;}

/** @return GL_TEXTURE_1D, GL_TEXTURE_2D, or GL_TEXTURE_3D. */
inline GLenum Texture::getType() const {return type;}

/** @return %Texture unit holding the data. */
inline GLuint Texture::getUnit() const {return unit;}

/** @return True if the texture was given a filename. */
inline bool Texture::hasFilename() const {return !filename.empty();}


#endif

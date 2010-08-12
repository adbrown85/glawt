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
using namespace std;


/** @brief OpenGL texture node.
 * 
 * Abstract base class for textures of various dimensions.  Provides some
 * basic texture capability, including finding an open texture unit and binding
 * the texture to that unit.  There are also two static methods, pause() and
 * restart() that disable and reenable all active texture units.
 * 
 * @note Add @e unit to @c GL_TEXTURE0 when passing directly to OpenGL.
 * 
 * @ingroup basic
 * @see Texture2D
 * @see Texture3D
 */
class Texture : public Node,
                public Applicable, public Nameable {
public:
	Texture(GLenum type, const Tag &tag);
	virtual void apply();
	virtual void associate();
	virtual void remove() {}
	virtual string toString() const;
public: // Accessors
	virtual string getFilename() const;
	virtual GLint getFootprint() const;
	virtual GLuint getHandle() const;
	virtual GLint getRawFootprint() const = 0;
	virtual GLenum getType() const;
	virtual GLuint getUnit() const;
	virtual bool hasFilename() const;
	virtual bool isCompressed() const;
public: // Utilities
	static list<Texture*> search(Node *node);
private:
	GLenum type;
	GLuint handle, unit;
	string filename;
};

/** @return Path to the file this texture was loaded from. */
inline string Texture::getFilename() const {return filename;}

/** @return OpenGL's unique identifier for this texture. */
inline GLuint Texture::getHandle() const {return handle;}

/** @return GL_TEXTURE_1D, GL_TEXTURE_2D, or GL_TEXTURE_3D. */
inline GLenum Texture::getType() const {return type;}

/** @return %Texture unit holding the data. */
inline GLuint Texture::getUnit() const {return unit;}

/** @return True if the texture was given a filename. */
inline bool Texture::hasFilename() const {return !filename.empty();}


#endif

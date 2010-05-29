/*
 * Texture.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include "common.h"
#include <queue>
#include "Node.hpp"                     // Base class
using namespace std;


/**
 * @ingroup basic
 * @brief OpenGL texture node.
 * 
 * Abstract base class for textures of various dimensions.  Provides some
 * basic texture capability, including finding an open texture unit and binding
 * the texture to that unit.  There are also two static methods, pause() and
 * restart() that disable and reenable all active texture units.
 * 
 * @note Add @e unit to @c GL_TEXTURE0 when passing directly to OpenGL.
 * 
 * @see Texture2D
 * @see Texture3D
 */
class Texture : public Applicable {
public:
	Texture(GLenum type, const Tag &tag);
	virtual void apply();
	virtual void associate();
	virtual string getFilename() const;
	virtual GLint getFootprint() const;
	virtual GLuint getHandle() const;
	virtual GLint getRawFootprint() const = 0;
	virtual string getName() const;
	static int getNumberOfActiveUnits();
	virtual GLenum getType() const;
	virtual int getUnit() const;
	virtual bool isCompressed() const;
	static void pause();
	virtual void remove();
	static void restart();
	static list<Texture*> search(Node *node);
	virtual string toString() const;
protected:
	GLenum type;
	GLuint handle;
	int unit;
	string filename, name;
private:
	static vector<GLenum> active_units;
};

/** @return Path to the file this texture was loaded from. */
inline string Texture::getFilename() const {return filename;}

/** @return OpenGL's unique identifier for this texture. */
inline GLuint Texture::getHandle() const {return handle;}

/** @return User's unique identifier for this texture. */
inline string Texture::getName() const {return name;}

/** @return Number of texture units being used. */
inline int Texture::getNumberOfActiveUnits() {return active_units.size();}

/** @return GL_TEXTURE_1D, GL_TEXTURE_2D, or GL_TEXTURE_3D. */
inline GLenum Texture::getType() const {return type;}

/** @return %Texture unit holding the data. */
inline int Texture::getUnit() const {return unit;}


#endif

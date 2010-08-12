/*
 * Texture2D.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP
#include "common.h"
#include "Texture.hpp"
#include "ImageFactory.hpp"
#include "Canvas.hpp"
using namespace std;


/** @brief %Texture node for images.
 * @ingroup basic
 */
class Texture2D : public Texture {
public:
	Texture2D(const Tag &tag);
	virtual void finalize();
	virtual string toString() const;
public:    // Accessors
	virtual GLint getRawFootprint() const;
	virtual int getSize() const;
public:    // Utilities
	static Texture2D* find(Node *node, const string &name);
private:
	GLenum format;
	int size;
};

/** @return width of the texture. */
inline int Texture2D::getSize() const {return size;}


#endif

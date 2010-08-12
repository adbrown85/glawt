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
	static Texture2D* find(Node *node, const string &name);
	virtual GLint getRawFootprint() const;
	virtual int getSize() const;
	virtual string toString() const;
private:
	GLenum format;
	int size;
	string formatText;
};

/** @return width of the texture. */
inline int Texture2D::getSize() const {return size;}


#endif

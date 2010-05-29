/*
 * Texture2D.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP
#include "common.h"
#include <IL/ilut.h>
#include "Texture.hpp"
using namespace std;


/** @brief %Texture node for images.
 * @ingroup basic
 */
class Texture2D : public Texture {
public:
	Texture2D(const Tag &tag);
	virtual void associate();
	static Texture2D* find(Node *node, const string &name);
	virtual GLint getRawFootprint() const;
	virtual int getSize() const;
	virtual string toString() const;
protected:
	virtual void generate();
	static void initLibraries();
	virtual void load();
private:
	static bool librariesLoaded;
	ILuint image;
	int size;
};

/** @return width of the texture. */
inline int Texture2D::getSize() const {return size;}


#endif

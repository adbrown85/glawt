/*
 * Texture2D.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <IL/ilut.h>
#include <iostream>
#include <sstream>
#include <string>
#include "Texture.hpp"


/**
 * @ingroup basic
 * @brief
 *     %Texture node for images.
 */
class Texture2D : public Texture {
public:
	
	Texture2D(const Tag &tag);
	virtual void associate();
	static void find(Node *node,
	                 Texture2D *&pointer,
	                 const string &name);
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


inline int Texture2D::getSize() const {return size;}


#endif

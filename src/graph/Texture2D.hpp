/*
 * Texture2D.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
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
 * @brief
 *     %Texture node for images.
 * @ingroup graph
 */
class Texture2D : public Texture {
	
	public :
		
		Texture2D(string name,
		          string filename);
		Texture2D(string name,
		          int size);
		Texture2D(const Tag &tag);
		virtual void associate();
		virtual string toString() const;
		
		virtual int getSize() {return size;}
		
		static void find(Node *node,
		                 Texture2D *&pointer,
		                 string name);
	
	private:
		
		ILuint image;
		int size;
		
		virtual void generate();
		virtual void init();
		virtual void initType() {type = GL_TEXTURE_2D;}
		virtual void initLibraries();
		virtual void load();
};


#endif

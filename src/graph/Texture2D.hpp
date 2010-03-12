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
 * @ingroup graph
 * @brief
 *     %Texture node for images.
 */
class Texture2D : public Texture {
	
	public :
		
		Texture2D(string name,
		          string filename);
		Texture2D(string name,
		          int size);
		Texture2D(const Tag &tag);
		virtual void associate();
		virtual int getSize() {return size;}
		virtual string toString() const;
	
	private:
		
		ILuint image;
		int size;
		
		virtual void generate();
		virtual void init();
		virtual void load();
	
	public: 
		
		static void find(Node *node,
		                 Texture2D *&pointer,
		                 string name);
	
	private:
		
		static bool librariesLoaded;
		
		static void initLibraries();
};


#endif

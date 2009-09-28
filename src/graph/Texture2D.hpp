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
		          int width,
		          int height);
		virtual void apply();
		virtual void associate();
		virtual void remove();
		
		virtual int getHeight() {return height;}
		virtual int getWidth() {return width;}
		
		static void find(Node *node,
		                 Texture2D *&pointer,
		                 string name);
	
	
	private:
		
		GLuint handle;
		ILuint image;
		int width, height;
		
		void generate();
		void initLibraries();
		void load();
};


#endif

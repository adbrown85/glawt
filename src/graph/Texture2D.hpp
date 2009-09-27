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
		
		Texture2D(string name);
		Texture2D(string filename,
		          string name="");
		virtual void apply();
		virtual void finalize();
		virtual void remove();
		
		static void find(Node *node,
		                 Texture2D *&pointer,
		                 string name);
	
	
	private:
		
		bool blank;
		GLuint handle;
		ILuint image;
		
		void generate();
		void initLibraries();
		void load();
};


#endif

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



class Texture2D : public Texture {
	
	
	public :
		
		Texture2D(string filename);
		virtual void apply();
		virtual void associate();
		virtual void remove();
	
	
	private:
		
		ILuint image;
		
		void initLibraries();
		void load();
};


#endif

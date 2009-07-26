/*
 * Texture.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <IL/ilut.h>
#include <iostream>
#include <string>
#include <typeinfo>
#include "Applicable.hpp"
#include "Node.hpp"
using namespace std;



class Texture : public Node,
                public Applicable {
	
	
	public:
		
		Texture(string filename);
		void apply();
		void associate();
		int getUnit() const {return unit;}
		void print() const;
		void remove();
		
		friend ostream& operator<<(ostream &stream,
		                           const Texture &texture);
	
	
	private:
		
		ILuint image;
		int unit;
		string filename;
		
		Texture();
		void load();
};


#endif

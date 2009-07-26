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
		virtual void apply() = 0;
		virtual void associate();
		virtual void print() const;
		virtual void remove() = 0;
		
		string getFilename() const {return filename;}
		string getType() const {return type;}
		int getUnit() const {return unit;}
		
		friend ostream& operator<<(ostream &stream,
		                           const Texture &texture);
	
	
	protected:
		
		int unit;
		string filename, type;
		
		Texture();
};


#endif

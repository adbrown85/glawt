/*
 * Texture3D.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef TEXTURE3D_HPP
#define TEXTURE3D_HPP
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
#include "Texture.hpp"
using namespace std;
typedef unsigned char byte;



class Texture3D : public Texture {
	
	
	public :
		
		Texture3D(string filename,
		          string name="");
		~Texture3D();
		virtual void associate();
		virtual void apply();
		void printSlice(int slice);
		virtual void remove();
		
		int getPitch() {return pitch;}
		int getWidth() {return width;}
	
	
	private:
		
		int pitch, width;
		byte ***data;
		
		Texture3D();
		void allocate();
		void deallocate();
		void load();
};


#endif

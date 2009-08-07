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
#include <iostream>
#include <string>
#include "Dataset.hpp"
#include "Texture.hpp"
using namespace std;



/**
 * @brief
 *     %Texture nodes for volumes.
 * @ingroup graph
 */
class Texture3D : public Texture {
	
	
	public :
		
		Texture3D(string filename,
		          string name="");
		virtual void apply();
		virtual void associate();
		virtual void remove();
		
		int getDepth() {return dataset.getDepth();}
		int getHeight() {return dataset.getHeight();}
		int getWidth() {return dataset.getWidth();}
	
	
	private:
		
		Dataset dataset;
		GLuint handle;
		
		Texture3D();
		void load();
};


#endif

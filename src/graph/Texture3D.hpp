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
#include "Tag.hpp"
#include "Texture.hpp"
using namespace std;


/**
 * @brief
 *     %Texture nodes for volumes.
 * @ingroup graph
 */
class Texture3D : public Texture {
	
	public :
		
		Texture3D(string name,
		          string filename);
		Texture3D(const Tag &tag);
		virtual void associate();
		
		int getDepth() {return dataset.getDepth();}
		int getHeight() {return dataset.getHeight();}
		int getWidth() {return dataset.getWidth();}
		static Texture3D* find(Node *node,
		                       const string &name);
	
	private:
		
		Dataset dataset;
		
		virtual void init();
		virtual void initType() {type = GL_TEXTURE_3D;}
		virtual void load();
};


#endif

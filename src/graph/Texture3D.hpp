/*
 * Texture3D.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
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
 * @ingroup graph
 * @brief
 *     %Texture nodes for volumes.
 */
class Texture3D : public Texture {
	
	public :
		
		Texture3D(const string &name,
		          const string &filename);
		Texture3D(const Tag &tag);
		virtual void associate();
		virtual Dataset* getDataset() {return &dataset;}
		virtual int getDepth() {return dataset.getDepth();}
		virtual int getHeight() {return dataset.getHeight();}
		virtual int getWidth() {return dataset.getWidth();}
		
		static Texture3D* find(Node *node,
		                       const string &name);
	
	private:
		
		Dataset dataset;
		
		virtual void init();
		virtual void load();
};


#endif

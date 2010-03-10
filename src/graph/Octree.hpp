/*
 * Octree.hpp
 *
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#ifndef OCTREE_HPP
#define OCTREE_HPP
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "Dataset.hpp"
#include "OctreeBuilder.hpp"
#include "OctreeNode.hpp"
#include "Tag.hpp"
#include "Texture.hpp"
#include "Texture3D.hpp"
using namespace std;


/**
 * 1D texture holding empty-space skipping information.
 */
class Octree : public Texture {
	
	public:
		
		Octree(const Tag &tag);
		~Octree();
		virtual void associate();
		virtual void finalize();
		virtual string toString() const;
	
	protected:
		
		unsigned char *array;
		Dataset *dataset;
		int size;
		OctreeNode *root;
		string link;
		
		virtual void initType() {type = GL_TEXTURE_1D;}
		virtual void load();
};


#endif

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
 * @ingroup graph
 * @brief
 *     1D texture holding empty-space skipping information.
 */
class Octree : public Texture {
	
	public:
		
		Octree(const Tag &tag);
		virtual ~Octree();
		virtual void associate();
		virtual void finalize();
		virtual void store(OctreeNode *node,
		                   int index,
		                   int depth);
		virtual string toString() const;
	
	protected:
		
		unsigned char *textureData;
		Dataset *dataset;
		int height, size, threshold;
		OctreeNode *root;
		string link;
		
		virtual void load();
};


#endif

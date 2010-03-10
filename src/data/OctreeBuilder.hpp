/*
 * OctreeBuilder.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef OCTREEBUILDER_HPP
#define OCTREEBUILDER_HPP
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "Dataset.hpp"
#include "OctreeNode.hpp"


/**
 * @ingroup data
 * @brief
 *     Builds an octree and returns the root node.
 */
class OctreeBuilder {
	
	public:
		
		OctreeBuilder(Dataset *dataset);
		~OctreeBuilder();
		
		OctreeNode* build();
		int getTotalNodes() const {return totalNodes;}
		int getTreeHeight() const {return treeHeight;}
		static int getTreeHeightOf(Dataset *dataset);
		string toString();
	
	protected:
		
		Dataset *dataset;
		int *offsets;
		int totalNodes;
		int treeHeight;
		
		OctreeNode* buildNode(Index &center,
		                      int depth);
		void buildNodeAsInner(const Index &center,
		                      int depth,
		                      OctreeNode *node);
		void buildNodeAsLeaf(const Index &center,
		                     int depth,
		                     OctreeNode *node);
		void initOffsets();
		Index offsetCenter(const Index &Center,
		                   int offset,
		                   int childNumber);
		Index offsetSample(const Index &Center,
		                   int sampleNumber);
};


#endif

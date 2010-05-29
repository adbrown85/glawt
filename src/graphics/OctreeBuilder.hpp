/*
 * OctreeBuilder.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef OCTREEBUILDER_HPP
#define OCTREEBUILDER_HPP
#include "common.h"
#include <cmath>
#include "Dataset.hpp"
#include "OctreeNode.hpp"


/** @brief Builds an octree from a dataset and returns the root node.
 * @ingroup graphics
 */
class OctreeBuilder {
public:
	OctreeBuilder(Dataset *dataset);
	~OctreeBuilder();
	OctreeNode* build();
	int* getOffsets() const;
	int getTotalNodes() const;
	int getTreeHeight() const;
	static int getTreeHeightOf(Dataset *dataset);
	void setThreshold(float threshold);
	string toString();
protected:
	OctreeNode* buildNode(Index &center, int depth);
	void buildNodeAsInner(const Index &center, int depth, OctreeNode *node);
	void buildNodeAsLeaf(const Index &center, int depth, OctreeNode *node);
	void initOffsets();
	Index offsetCenter(const Index &Center, int offset, int childNumber);
	Index offsetSample(const Index &Center, int sampleNumber);
private:
	Dataset *dataset;
	float threshold;
	int *offsets, totalNodes, treeHeight;
};


inline int* OctreeBuilder::getOffsets() const {return offsets;}

/** @return Total number of nodes in the tree. */
inline int OctreeBuilder::getTotalNodes() const {return totalNodes;}

/** @return distance from root to a leaf. */
inline int OctreeBuilder::getTreeHeight() const {return treeHeight;}

/** Sets the number that determines if a node is empty. */
inline void OctreeBuilder::setThreshold(float t) {this->threshold = t;}




#endif

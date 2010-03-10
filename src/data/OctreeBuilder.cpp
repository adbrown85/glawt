/*
 * OctreeBuilder.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "OctreeBuilder.hpp"


OctreeBuilder::OctreeBuilder(Dataset *dataset) {
	
	// Basics
	this->dataset = dataset;
	this->treeHeight = getTreeHeightOf(dataset);
	totalNodes = 0;
	threshold = 0;
	
	// Offsets
	offsets = new int[treeHeight+1];
	offsets[0] = dataset->getMaximumDimension() / 2;
	for (int i=1; i<treeHeight+1; ++i) {
		offsets[i] = offsets[i-1] / 2;
	}
}


OctreeBuilder::~OctreeBuilder() {
	
	delete[] offsets;
}


OctreeNode* OctreeBuilder::build() {
	
	Index center;
	
	// Build up from root node
	center.set(offsets[0]);
	return buildNode(center, 0);
}


OctreeNode* OctreeBuilder::buildNode(Index &center,
                                     int depth) {
	
	OctreeNode *node;
	
	node = new OctreeNode();
	++totalNodes;
	if (depth == treeHeight) {
		buildNodeAsLeaf(center, depth, node);
	} else {
		buildNodeAsInner(center, depth, node);
	}
	return node;
}


void OctreeBuilder::buildNodeAsInner(const Index &center,
                                     int depth,
                                     OctreeNode *node) {
	
	bool empty;
	Index childCenter;
	OctreeNode *childNode;
	
	// Build children
	empty = true;
	depth += 1;
	for (int i=0; i<8; ++i) {
		childCenter = offsetCenter(center, offsets[depth], i);
		childNode = buildNode(childCenter, depth);
		node->setChild(i, childNode);
		if (!childNode->isEmpty()) {
			empty = false;
		}
	}
	node->setEmpty(empty);
}


void OctreeBuilder::buildNodeAsLeaf(const Index &center,
                                    int depth,
                                    OctreeNode *node) {
	
	GLenum type;
	Index sampleIndex;
	void *value;
	
	// Check each voxel around sample point
	type = dataset->getType();
	for (int i=0; i<8; ++i) {
		sampleIndex = offsetSample(center, i);
		switch (type) {
			case GL_UNSIGNED_BYTE:
				if (dataset->getAsByte(sampleIndex) > (int)threshold)
					return;
				break;
			case GL_FLOAT:
				if (dataset->getAsFloat(sampleIndex) > threshold)
					return;
				break;
			case GL_SHORT:
				if (dataset->getAsShort(sampleIndex) > (short)threshold)
					return;
				break;
			default:
				throw "[OctreeBuilder] Dataset type not supported.";
		}
	}
	node->setEmpty(true);
}


/**
 * Computes the height of the tree required for a dataset.
 * 
 * Calculated as (log base 8 of the total samples) - 1;
 * 
 * @param dataset
 *     Pointer to the Dataset to use.
 */
int OctreeBuilder::getTreeHeightOf(Dataset *dataset) {
	
	int maxDimension, totalSamples;
	
	// Get size of dataset
	maxDimension = dataset->getMaximumDimension();
	totalSamples = maxDimension * maxDimension * maxDimension;
	
	// Compute height using log_8(size) - 1
	return (int)(log(totalSamples) / log(8)) - 1;
}


Index OctreeBuilder::offsetCenter(const Index &center,
                                  int offset,
                                  int childNumber) {
	
	switch (childNumber) {
		case 0: return center + Index(-offset,-offset,-offset);
		case 1: return center + Index(-offset,+offset,-offset);
		case 2: return center + Index(+offset,-offset,-offset);
		case 3: return center + Index(+offset,+offset,-offset);
		case 4: return center + Index(-offset,-offset,+offset);
		case 5: return center + Index(-offset,+offset,+offset);
		case 6: return center + Index(+offset,-offset,+offset);
		case 7: return center + Index(+offset,+offset,+offset);
		default: throw "[OctreeBuilder] Index out of bounds.";
	}
}


Index OctreeBuilder::offsetSample(const Index &center,
                                  int sampleNumber) {
	
	switch (sampleNumber) {
		case 0: return center + Index(-1,-1,-1);
		case 1: return center + Index(-1, 0,-1);
		case 2: return center + Index( 0,-1,-1);
		case 3: return center + Index( 0, 0,-1);
		case 4: return center + Index(-1,-1, 0);
		case 5: return center + Index(-1, 0, 0);
		case 6: return center + Index( 0,-1, 0);
		case 7: return center + Index( 0, 0, 0);
		default: throw "[OctreeBuilder] Index out of bounds.";
	}
}


string OctreeBuilder::toString() {
	
	stringstream stream;
	
	// Format
	stream << "OctreeBuilder " << "treeHeight=" << treeHeight;
	return stream.str();
}


/*
 * Octree.glsl
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Ray.glsl"
#include "BoundingBox.glsl"
#include "BoundaryTimes.glsl"
#include "OctreeNode.glsl"


bool Octree_isEmpty(in sampler1D octree,
                    in int length,
                    in OctreeNode node) {
	
	float index;
	vec4 texel;
	
	// Check if index in octree texture is empty
	index = float(node.key) / length;
	texel = texture1D(octree, index);
	if (texel.x > 0.5) {
		return true;
	} else {
		return false;
	}
}


OctreeNode Octree_findEntryChild(in OctreeNode parentNode,
                                 in BoundaryTimes parentTimes,
                                 in childDepth) {
	
	int entryPlane, firstChildKey;
	OctreeNode childNode;
	
	// Initialize
	firstChildKey = parentNode.key + 1;
	entryPlane = Octree_findEntryPlane(parentTimes);
	
	// Enters on bottom face
	if (entryPlane == 0) {
		if (parentTimes.th.x < parentTimes.t0.y) {
			childNode.name = 1;
			childNode.key = firstChildKey + step[childDepth];
		} else {
			childNode.name = 0;
			childNode.key = firstChildKey;
		}
	}
	
	// Enters on left side, then top or bottom
	else if (entryPlane == 1) {
		if (parentTimes.th.y < parentTimes.t0.x) {
			childNode.name = 2;
			childNode.key = firstChildKey + 2*step[childDepth];
		} else {
			childNode.name = 0;
			childNode.key = firstChildKey;
		}
	}
	
	// Finish
	return childNode;
}


int Octree_findEntryPlane(in BoundaryTimes parentTimes) {
	
	if (parentTimes.t0.x > parentTimes.t0.y) {
		if (parentTimes.t0.x > parentTimes.t0.z) {
			return 0;
		} else {
			return 2;
		}
	} else {
		if (parentTimes.t0.y > parentTimes.t0.z) {
			return 1;
		} else {
			return 2;
		}
	}
}


vec4 Octree_sample(in sampler3D volume,
                   in sampler1D octree,
                   in int length,
                   in Ray ray,
                   in OctreeNode node,
                   in BoundaryTimes times,
                   in int height,
                   in int depth) {
	
	// Check if empty
	if (Octree_isEmpty(octree, length, node)) {
		return vec4(1,0,0,1);
	}
	
	// Check if leaf
	if (depth == height) {
		return vec4(
	}
	
	++depth;
	return Octree_sampleChildren(volume, octree, length, ray,
	                             node, times, height, depth);
}



vec4 Octree_sampleChildren(in sampler3D volume,
                           in sampler1D octree,
                           in int length,
                           in Ray ray,
                           in OctreeNode parentNode,
                           in BoundaryTimes parentTimes,
                           in int height,
                           in int parentDepth) {
	
	BoundaryTimes childTimes;
	int childDepth=parentDepth+1;
	OctreeNode childNode;
	
	// First child
	childNode = Octree_findFirstChild(parentNode, parentTimes, childDepth);
	
	// Next child until out of parent
}


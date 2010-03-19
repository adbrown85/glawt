/*
 * Octree.glsl
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Colors.glsl"
#include "Ray.glsl"
#include "BoundingBox.glsl"
#include "BoundaryTimes.glsl"
#include "OctreeNode.glsl"
#define XZ_PLANE 0
#define YZ_PLANE 1
#define XY_PLANE 2
int steps[8];


void Octree_init() {
	
	steps[0] = 1;
	steps[1] = 9;
	steps[2] = 73;
	steps[3] = 585;
	steps[4] = 4681;
	steps[5] = 37449;
	steps[6] = 299593;
	steps[7] = 2396745;
}


bool Octree_isEmpty(in sampler1D octree,
                    in int length,
                    in OctreeNode node) {
	
	float index;
	vec4 texel;
	
	// Check if index in octree texture is empty
	index = float(node.key) / float(length);
	texel = texture1D(octree, index);
	if (texel.x > 0.5) {
		return true;
	} else {
		return false;
	}
}


int Octree_findEntryPlane(in BoundaryTimes parentTimes) {
	
	// X hits after Y, then compare to Z
	if (parentTimes.t0.x > parentTimes.t0.y) {
		if (parentTimes.t0.x > parentTimes.t0.z) {
			return YZ_PLANE;
		} else {
			return XY_PLANE;
		}
	}
	
	// Y hits after X, then compare to Z
	else {
		if (parentTimes.t0.y > parentTimes.t0.z) {
			return XZ_PLANE;
		} else {
			return XY_PLANE;
		}
	}
}


OctreeNode Octree_findEntryChild(in OctreeNode parentNode,
                                 in BoundaryTimes times,
                                 in int height) {
	
	int entryPlane, firstChildKey;
	OctreeNode childNode;
	
	// Find entry plane
	entryPlane = Octree_findEntryPlane(times);
	switch (entryPlane) {
		
		// Enters on front face
		case XY_PLANE:
			if (times.th.x < times.t0.z) {
				if (times.th.y < times.t0.z) {
					childNode.name = 3;
				} else {
					childNode.name = 1;
				}
			} else {
				if (times.th.y < times.t0.z) {
					childNode.name = 2;
				} else {
					childNode.name = 0;
				}
			}
			break;
		
		// Enters on left face
		case YZ_PLANE:
			if (times.th.y < times.t0.x) {
				if (times.th.z < times.t0.x) {
					childNode.name = 6;
				} else {
					childNode.name = 2;
				}
			} else {
				if (times.th.z < times.t0.x) {
					childNode.name = 4;
				} else {
					childNode.name = 0;
				}
			}
			break;
		
		// Enters on bottom face
		case XZ_PLANE:
			if (times.th.x < times.t0.y) {
				if (times.th.z < times.t0.y) {
					childNode.name = 5;
				} else {
					childNode.name = 1;
				}
			} else {
				if (times.th.z < times.t0.y) {
					childNode.name = 4;
				} else {
					childNode.name = 0;
				}
			}
			break;
	}
	
	// Finish
	firstChildKey = parentNode.key + 1;
	childNode.key = firstChildKey + (childNode.name * steps[height]);
	return childNode;
}


vec4 Octree_sampleChildren(in sampler3D volume,
                           in sampler1D octree,
                           in int length,
                           in Ray ray,
                           in OctreeNode parentNode,
                           in BoundaryTimes parentTimes,
                           in int height) {
	
	
	// Child where the ray enters the parent
	return Octree_sample(volume, octree, length, ray, childNode, parentTimes, height);
/*
	switch (childNode.name) {
		case 0: return GREEN;
		case 1: return BLUE;
		case 2: return YELLOW;
		case 3: return WHITE;
		case 4: return ORANGE;
		case 5: return PURPLE;
		case 6: return BROWN;
		case 7: return GRAY;
	}
*/
}


vec4 Octree_sample(in sampler3D volume,
                   in sampler1D octree,
                   in int length,
                   in Ray ray,
                   in int height) {
	
	bool outOfVolume;
	BoundingBox box;
	BoundaryTimes time[8];
	float result;
	OctreeNode node[8];
	
	// Initialize
	BoundingBox_(box);
	Octree_init();
	times = BoundingBox_calculateTimes(box, ray);
	OctreeNode_(node[height], 0, 0);
	
/*
	while (!outOfVolume) {
*/
	
		// Check if empty
		if (Octree_isEmpty(octree, length, node[height])) {
			return RED;
		}
		
		// Check if leaf
		if (height == 0) {
			return BLUE;
		}
		
		// Sample children
		--height;
		node[height] = Octree_findEntryChild(parentNode, parentTimes, height);
/*
	}
*/
}


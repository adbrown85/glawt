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
#define MAX_HEIGHT 8
#define FIRST_STEP 1
#define SECOND_STEP 2
#define FIRST_CHILD 0
#define ROOT_KEY 0
#define NULL_NODE OctreeNode_()
int jump[MAX_HEIGHT];


bool Octree_init(in int height) {
	
	// Check height
	if (height > MAX_HEIGHT) {
		gl_FragColor = RED;
		return false;
	}
	
	// Initialize jumps
	jump[0] = 1;
	jump[1] = 9;
	jump[2] = 73;
	jump[3] = 585;
	jump[4] = 4681;
	jump[5] = 37449;
	jump[6] = 299593;
	jump[7] = 2396745;
	
	// Finish
	return true;
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


/**
 * Gets the child of a node.
 * 
 * @param pNode Parent node
 * @param cName Name of the child node to get
 * @param cHeight Height of the subtree at the child's depth
 * @return node with key and name set properly
 */
OctreeNode Octree_getChild(in OctreeNode pNode,
                           in int cName,
                           in int cHeight) {
	
	OctreeNode cNode;
	
	cNode.name = cName;
	cNode.key = (pNode.key + 1) + (cName * jump[cHeight]);
	return cNode;
}


/**
 * Finds the plane ray hits when it enters a node.
 * 
 * @param times Times of the node
 * @return integer representing one of the planes
 */
int Octree_findEntryPlane(in BoundaryTimes times) {
	
	// X hits after Y, then compare to Z
	if (times.t0.x > times.t0.y) {
		if (times.t0.x > times.t0.z) {
			return YZ_PLANE;
		} else {
			return XY_PLANE;
		}
	}
	
	// Y hits after X, then compare to Z
	else {
		if (times.t0.y > times.t0.z) {
			return XZ_PLANE;
		} else {
			return XY_PLANE;
		}
	}
}


/**
 * Finds first child node ray hits when it enters a node.
 * 
 * @param pNode Parent Node
 * @param pTimes Parent Times
 * @param cHeight Height of the subtree at the child's depth
 * @return the child node that is hit first
 */
OctreeNode Octree_findEntryChild(in OctreeNode pNode,
                                 in BoundaryTimes pTimes,
                                 in int cHeight) {
	
	int entryPlane, cName=0;
	
	// Find entry plane
	entryPlane = Octree_findEntryPlane(pTimes);
	switch (entryPlane) {
		
		// Enters on front face
		case XY_PLANE:
			if (pTimes.th.x < pTimes.t0.z) {
				if (pTimes.th.y < pTimes.t0.z) {
					cName = 3;
				} else {
					cName = 1;
				}
			} else {
				if (pTimes.th.y < pTimes.t0.z) {
					cName = 2;
				} else {
					cName = 0;
				}
			}
			break;
		
		// Enters on left face
		case YZ_PLANE:
			if (pTimes.th.y < pTimes.t0.x) {
				if (pTimes.th.z < pTimes.t0.x) {
					cName = 6;
				} else {
					cName = 2;
				}
			} else {
				if (pTimes.th.z < pTimes.t0.x) {
					cName = 4;
				} else {
					cName = 0;
				}
			}
			break;
		
		// Enters on bottom face
		case XZ_PLANE:
			if (pTimes.th.x < pTimes.t0.y) {
				if (pTimes.th.z < pTimes.t0.y) {
					cName = 5;
				} else {
					cName = 1;
				}
			} else {
				if (pTimes.th.z < pTimes.t0.y) {
					cName = 4;
				} else {
					cName = 0;
				}
			}
			break;
	}
	
	// Finish
	return Octree_getChild(pNode, cName, cHeight);
}


/**
 * Finds the plane the ray leaves a node through.
 * 
 * @param times Times of the node
 */
/*
int Octree_findExitPlane(in BoundaryTimes times) {
	
	// X hits before Y, then compare to Z
	if (times.t1.x < times.t1.y) {
		if (times.t1.x < times.t1.z) {
			return YZ_PLANE;
		} else {
			return XY_PLANE;
		}
	}
	
	// Y hits before X, then compare to Z
	else {
		if (times.t1.y < times.t1.z) {
			return XZ_PLANE;
		} return {
			return XY_PLANE;
		}
	}
}
*/


/**
 * Finds next child ray enters by examining last child and its times.
 * 
 * @param pNode Parent Node
 * @param cTimesLast Times of the last child node
 * @param cHeight Height of the subtree at the child's depth
 * @param cNodeLast Last child node
 * @return the next child node
 */
/*
OctreeNode Octree_findNextChild(in OctreeNode pNode,
                                in BoundaryTimes cTimesLast,
                                in int cHeight,
                                in OctreeNode cNodeLast) {
	
	int exitPlane;
	
	exitPlane = Octree_findExitPlane(cTimesLast);
	switch (cNodeLast.name) {
	case 0:
		switch (exitPlane) {
		case XZ_PLANE: return Octree_getChild(pNode, 2, cHeight);
		case YZ_PLANE: return Octree_getChild(pNode, 1, cHeight);
		case XY_PLANE: return Octree_getChild(pNode, 4, cHeight);
		}
	case 1:
		switch (exitPlane) {
		case XZ_PLANE: return Octree_getChild(pNode, 3, cHeight);
		case YZ_PLANE: return NULL_NODE;
		case XY_PLANE: return Octree_getChild(pNode, 5, cHeight);
		}
	case 2:
		switch (exitPlane) {
		case XZ_PLANE: return NULL_NODE;
		case YZ_PLANE: return Octree_getChild(pNode, 3, cHeight);
		case XY_PLANE: return Octree_getChild(pNode, 6, cHeight);
		}
	case 3:
		switch (exitPlane) {
		case XZ_PLANE: return NULL_NODE;
		case YZ_PLANE: return NULL_NODE;
		case XY_PLANE: return Octree_getChild(pNode, 7, cHeight);
		}
	case 4:
		switch (exitPlane) {
		case XZ_PLANE: return Octree_getChild(pNode, 6, cHeight);
		case YZ_PLANE: return Octree_getChild(pNode, 5, cHeight);
		case XY_PLANE: return NULL_NODE;
		}
	case 5:
		switch (exitPlane) {
		case XZ_PLANE: return Octree_getChild(pNode, 7, cHeight);
		case YZ_PLANE: return NULL_NODE;
		case XY_PLANE: return NULL_NODE;
		}
	case 6:
		switch (exitPlane) {
		case XZ_PLANE: return NULL_NODE;
		case YZ_PLANE: return Octree_getChild(pNode, 7, cHeight);
		case XY_PLANE: return NULL_NODE;
		}
	case 7:
		switch (exitPlane) {
		case XZ_PLANE: return NULL_NODE;
		case YZ_PLANE: return NULL_NODE;
		case XY_PLANE: return NULL_NODE;
		}
	}
}
*/


/**
 * Determines change in boundaries between a parent and child node.
 * 
 * @param cNode Child node
 * @return vector with 1 in component if that direction changed
 */
/*
vec3 Octree_getChange(in OctreeNode cNode) {
	
	switch (cNode.name) {
	case 0: return vec3(0,0,0);
	case 1: return vec3(1,0,0);
	case 2: return vec3(0,1,0);
	case 3: return vec3(1,1,0);
	case 4: return vec3(0,0,1);
	case 5: return vec3(1,0,1);
	case 6: return vec3(0,1,1);
	case 7: return vec3(1,1,1);
	}
}
*/


/**
 * Finds the times of a child node by halving its parent's times.
 * 
 * @param cNode Child node
 * @param pTimes Parent times
 * @return times of the child node
 */
/*
BoundaryTimes Octree_updateTimes(in OctreeNode cNode,
                                 in BoundaryTimes pTimes) {
	
	BoundaryTimes cTimes;
	vec3 change, delta;
	
	// Initialize
	change = Octree_getChange(cNode);
	delta = (pTimes.t1 - pTime.t0) * 0.5;
	
	// Calculate child times
	cTimes.t0 = pTimes.t0 + (delta * change);
	cTimes.t1 = cTimes.t0 + delta;
	cTimes.th = (cTimes.t0 + cTimes.t1) * 0.5;
	return cTimes;
}
*/


/*
void Octree_sampleAsLeaf(in Ray ray,
                         BoundaryTimes times,
                         in sampler3D volume) {
	
	float tEnter, tLeave;
	vec4 rayPos, sample;
	
	BoundaryTimes_getIntersections(times, tEnter, tLeave);
	t = tEnter + 0.05;
	while (t < tLeave) {
		rayPos = ray.o + (ray.d * t);
		sample = texture3D(volume, rayPos.stp);
		sample.a = sample.x;
		if (sample.a > 0.01) {
			gl_FragColor = mix(gl_FragColor, sample, sample.a);
			if (gl_FragColor.a > 0.9)
				break;
		}
		t += 0.05;
	}
}
*/


void Octree_sample(in sampler3D volume,
                   in sampler1D octree,
                   in int length,
                   in Ray ray,
                   in int height) {
	
	BoundingBox box;
	BoundaryTimes times[MAX_HEIGHT];
	int depth, cDepth, cHeight, step[MAX_HEIGHT];
	OctreeNode node[MAX_HEIGHT];
	
	// Initialize octree
	if (!Octree_init(height)) {
		return;
	}
	
	// Initialize bounding box and times
	box = BoundingBox_();
	times[0] = BoundingBox_calculateTimes(box, ray);
	
	// Initialize depth and height
	depth = 0;
	cHeight = height - 1;
	
	// Initialize nodes and steps
	node[0] = OctreeNode_(ROOT_KEY, FIRST_CHILD);
	step[0] = FIRST_STEP;
	for (int i=1; i<MAX_HEIGHT; ++i) {
		node[i] = NULL_NODE;
		step[i] = FIRST_STEP;
	}
	
	// While in volume
	//while (depth >= 0) {
		switch (step[depth]) {
		case FIRST_STEP:
			
			// Check if empty
			if (Octree_isEmpty(octree, length, node[depth])) {
				gl_FragColor = RED;
				--depth;
				++cHeight;
				return; //continue;
			}
			
			// Check if leaf
			if (depth == height) {
				//Octree_sampleAsLeaf(ray, times[depth]);
				gl_FragColor = GREEN;
				--depth;
				++cHeight;
				return; //continue;
			}
		
		case SECOND_STEP:
			
			// Sample children
			cDepth = depth + 1;
			if (node[cDepth].name == NULL) {
				node[cDepth] = Octree_findEntryChild(node[depth],
				                                     times[depth],
				                                     cHeight);
			} else {
				node[cDepth] = Octree_findNextChild(node[depth],
				                                    times[depth],
				                                    cHeight,
				                                    node[cDepth]);
			}
			switch (node[cDepth].name) {
			case 0: gl_FragColor = GREEN; break;
			case 1: gl_FragColor = BLUE; break;
			case 2: gl_FragColor = YELLOW; break;
			case 3: gl_FragColor = WHITE; break;
			case 4: gl_FragColor = ORANGE; break;
			case 5: gl_FragColor = PURPLE; break;
			case 6: gl_FragColor = BROWN; break;
			case 7: gl_FragColor = GRAY; break;
			}
			
			
/*
			
			// Check if out of volume
			if (node[cDepth].name == NULL) {
				--depth;
				++cHeight;
			}
			
			// Otherwise move to child
			else {
				times[cDepth] = Octree_updateTimes(node[cDepth], times[depth]);
				step[depth] = SECOND_STEP;
				step[cDepth] = FIRST_STEP;
				++depth;
				--cHeight;
			}
*/
		}
	//}
}


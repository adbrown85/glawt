/* 
 * octree.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
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

// Constants
int jump[MAX_HEIGHT]=int[MAX_HEIGHT](1,9,73,585,4681,37449,299593,2396745);

// Uniforms
uniform sampler2D buffer;
uniform sampler3D volume;
uniform usampler1D octree;
uniform int height;

// Inputs and outputs
in vec4 TexCoord;
out vec4 FragColor;

// Globals
BoundaryTimes times[MAX_HEIGHT];
BoundingBox box=BoundingBox_();
OctreeNode node[MAX_HEIGHT];
Ray ray;
int depth=0, cDepth;


/**
 * Updates the child of a node.
 * 
 * @param cName Name of the child node to get
 */
void updateChild(in int cName) {
	
	node[cDepth].name = cName;
	node[cDepth].key = (node[depth].key + 1) + (cName * jump[height-cDepth]);
}


/**
 * Finds the plane ray hits when it enters a node.
 * 
 * @return integer representing one of the planes
 */
int findEntryPlane() {
	
	// X hits after Y, then compare to Z
	if (times[depth].t0.x > times[depth].t0.y) {
		if (times[depth].t0.x > times[depth].t0.z) {
			return YZ_PLANE;
		} else {
			return XY_PLANE;
		}
	}
	
	// Y hits after X, then compare to Z
	else {
		if (times[depth].t0.y > times[depth].t0.z) {
			return XZ_PLANE;
		} else {
			return XY_PLANE;
		}
	}
}


/**
 * Finds first child node ray hits when it enters a node.
 */
void findEntryChild() {
	
	// Find entry plane
	switch (findEntryPlane()) {
		
		// Enters on front face
		case XY_PLANE:
			if (times[depth].th.x < times[depth].t0.z) {
				if (times[depth].th.y < times[depth].t0.z) {
					updateChild(3);
				} else {
					updateChild(1);
				}
			} else {
				if (times[depth].th.y < times[depth].t0.z) {
					updateChild(2);
				} else {
					updateChild(0);
				}
			}
			break;
		
		// Enters on left face
		case YZ_PLANE:
			if (times[depth].th.y < times[depth].t0.x) {
				if (times[depth].th.z < times[depth].t0.x) {
					updateChild(6);
				} else {
					updateChild(2);
				}
			} else {
				if (times[depth].th.z < times[depth].t0.x) {
					updateChild(4);
				} else {
					updateChild(0);
				}
			}
			break;
		
		// Enters on bottom face
		case XZ_PLANE:
			if (times[depth].th.x < times[depth].t0.y) {
				if (times[depth].th.z < times[depth].t0.y) {
					updateChild(5);
				} else {
					updateChild(1);
				}
			} else {
				if (times[depth].th.z < times[depth].t0.y) {
					updateChild(4);
				} else {
					updateChild(0);
				}
			}
			break;
	}
}


/**
 * Finds the plane the ray leaves a node through.
 * 
 * @param times Times of the node
 */
int findExitPlane() {
	
	// X hits before Y, then compare to Z
	if (times[cDepth].t1.x < times[cDepth].t1.y) {
		if (times[cDepth].t1.x < times[cDepth].t1.z) {
			return YZ_PLANE;
		} else {
			return XY_PLANE;
		}
	}
	
	// Y hits before X, then compare to Z
	else {
		if (times[cDepth].t1.y < times[cDepth].t1.z) {
			return XZ_PLANE;
		} else {
			return XY_PLANE;
		}
	}
}


/**
 * Finds next child ray enters by examining last child and its times.
 * 
 * @return the next child node
 */
void findNextChild() {
	
	int exitPlane=findExitPlane();
	
	switch (node[cDepth].name) {
	case 0:
		switch (exitPlane) {
		case XZ_PLANE: updateChild(2); return;
		case YZ_PLANE: updateChild(1); return;
		case XY_PLANE: updateChild(4); return;
		}
	case 1:
		switch (exitPlane) {
		case XZ_PLANE: updateChild(3); return;
		case YZ_PLANE: node[cDepth].name = -1; return;
		case XY_PLANE: updateChild(5); return;
		}
	case 2:
		switch (exitPlane) {
		case XZ_PLANE: node[cDepth].name = -1; return;
		case YZ_PLANE: updateChild(3); return;
		case XY_PLANE: updateChild(6); return;
		}
	case 3:
		switch (exitPlane) {
		case XZ_PLANE: node[cDepth].name = -1; return;
		case YZ_PLANE: node[cDepth].name = -1; return;
		case XY_PLANE: updateChild(7); return;
		}
	case 4:
		switch (exitPlane) {
		case XZ_PLANE: updateChild(6); return;
		case YZ_PLANE: updateChild(5); return;
		case XY_PLANE: node[cDepth].name = -1; return;
		}
	case 5:
		switch (exitPlane) {
		case XZ_PLANE: updateChild(7); return;
		case YZ_PLANE: node[cDepth].name = -1; return;
		case XY_PLANE: node[cDepth].name = -1; return;
		}
	case 6:
		switch (exitPlane) {
		case XZ_PLANE: node[cDepth].name = -1; return;
		case YZ_PLANE: updateChild(7); return;
		case XY_PLANE: node[cDepth].name = -1; return;
		}
	case 7:
		switch (exitPlane) {
		case XZ_PLANE: node[cDepth].name = -1; return;
		case YZ_PLANE: node[cDepth].name = -1; return;
		case XY_PLANE: node[cDepth].name = -1; return;
		}
	}
}


/**
 * Determines change in boundaries between a parent and child node.
 * 
 * @param cName Child node name
 * @return vector with 1 in component if that direction changed
 */
vec3 getChange(in int cName) {
	
	switch (cName) {
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


/**
 * Finds the times of a child node by halving its parent's times.
 * 
 * @return times of the child node
 */
void updateTimes() {
	
	vec3 change, delta;
	
	// Initialize
	change = getChange(node[cDepth].name);
	delta = (times[depth].t1 - times[depth].t0) * 0.5;
	
	// Calculate child times
	times[cDepth].t0 = times[depth].t0 + (delta * change);
	times[cDepth].t1 = times[cDepth].t0 + delta;
	times[cDepth].th = (times[cDepth].t0 + times[cDepth].t1) * 0.5;
}


void sampleAsLeaf() {
	
	float t, tExit;
	vec4 rayPos, texel;
	
	BoundaryTimes_getIntersections(times[depth], t, tExit);
	while (t < tExit) {
		rayPos = ray.o + (ray.d * t);
		texel = texture(volume, rayPos.stp);
		texel.a = texel.x;
		if (texel.a > 0.01) {
			FragColor = mix(FragColor, texel, texel.a);
			if (FragColor.a > 0.9) {
				break;
			}
		}
		t += 0.1;
	}
}


/**
 * Calculates when the ray hits the bounding box.
 */
void initTimes() {
	
	// Lower boundary
	times[0].t0.x = (box.lower.x - ray.o.x) / ray.d.x;
	times[0].t0.y = (box.lower.y - ray.o.y) / ray.d.y;
	times[0].t0.z = (box.lower.z - ray.o.z) / ray.d.z;
	
	// Upper boundary
	times[0].t1.x = (box.upper.x - ray.o.x) / ray.d.x;
	times[0].t1.y = (box.upper.y - ray.o.y) / ray.d.y;
	times[0].t1.z = (box.upper.z - ray.o.z) / ray.d.z;
	
	// Center
	times[0].th.x = (box.center.x - ray.o.x) / ray.d.x;
	times[0].th.y = (box.center.y - ray.o.y) / ray.d.y;
	times[0].th.z = (box.center.z - ray.o.z) / ray.d.z;
}


void sample() {
	
	BoundingBox box=BoundingBox_();
	int step[MAX_HEIGHT];
	
	// Initialize
	initTimes();
	node[0] = OctreeNode(ROOT_KEY, FIRST_CHILD);
	step[0] = SECOND_STEP;
	for (int i=1; i<MAX_HEIGHT; ++i) {
		node[i].name = -1;
		step[i] = FIRST_STEP;
	}
	
	// While in volume
	FragColor = BLACK;
	while (depth >= 0) {
		switch (step[depth]) {
		case FIRST_STEP:
			
			// If empty skip it and move back up
			if (texelFetch(octree,node[depth].key,0).r != uint(0)) {
				--depth;
				continue;
			}
			
			// If leaf sample it and move back up
			if (depth == height) {
				sampleAsLeaf();
				--depth;
				continue;
			}
		
		case SECOND_STEP:
			
			// Find first or next child
			cDepth = depth + 1;
			if (node[cDepth].name == -1) {
				findEntryChild();
			} else {
				findNextChild();
				if (node[cDepth].name == -1) {
					--depth;
					continue;
				}
			}
			
			// Move to next child
			updateTimes();
			step[depth] = SECOND_STEP;
			step[cDepth] = FIRST_STEP;
			++depth;
		}
	}
}


void main() {
	
	// Initialize ray
	ray.o = TexCoord;
	ray.d = normalize(texelFetch(buffer,ivec2(gl_FragCoord.xy),0) - TexCoord);
	if (Ray_isNegative(ray)) {
		FragColor = BLACK;
		return;
	}
	
	// Sample
	sample();
}


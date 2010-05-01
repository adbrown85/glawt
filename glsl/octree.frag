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
uniform int jump[MAX_HEIGHT]=int[MAX_HEIGHT](1,9,73,585,4681,37449,299593,2396745);

// Uniforms
uniform sampler2D buffer;
uniform sampler3D volume;
uniform usampler1D octree;
uniform int height;

// Inputs and outputs
in vec4 TexCoord;
out vec4 FragColor;

// Globals
vec3 t0[MAX_HEIGHT], t1[MAX_HEIGHT], th[MAX_HEIGHT];
BoundingBox box=BoundingBox_();
OctreeNode node[MAX_HEIGHT];
Ray ray;
int d=0, c;


/**
 * Updates the child of a node.
 * 
 * @param cName Name of the child node to get
 */
void updateChild(in int cName) {
	
	node[c].name = cName;
	node[c].key = (node[d].key + 1) + (cName * jump[height-c]);
}


/**
 * Finds the plane ray hits when it enters a node.
 * 
 * @return integer representing one of the planes
 */
int findEntryPlane() {
	
	// X hits after Y, then compare to Z
	if (t0[d].x > t0[d].y) {
		if (t0[d].x > t0[d].z) {
			return YZ_PLANE;
		} else {
			return XY_PLANE;
		}
	}
	
	// Y hits after X, then compare to Z
	else {
		if (t0[d].y > t0[d].z) {
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
			if (th[d].x < t0[d].z) {
				if (th[d].y < t0[d].z) {
					updateChild(3);
				} else {
					updateChild(1);
				}
			} else {
				if (th[d].y < t0[d].z) {
					updateChild(2);
				} else {
					updateChild(0);
				}
			}
			break;
		
		// Enters on left face
		case YZ_PLANE:
			if (th[d].y < t0[d].x) {
				if (th[d].z < t0[d].x) {
					updateChild(6);
				} else {
					updateChild(2);
				}
			} else {
				if (th[d].z < t0[d].x) {
					updateChild(4);
				} else {
					updateChild(0);
				}
			}
			break;
		
		// Enters on bottom face
		case XZ_PLANE:
			if (th[d].x < t0[d].y) {
				if (th[d].z < t0[d].y) {
					updateChild(5);
				} else {
					updateChild(1);
				}
			} else {
				if (th[d].z < t0[d].y) {
					updateChild(4);
				} else {
					updateChild(0);
				}
			}
			break;
	}
}


/**
 * Finds the plane the ray leaves a child node through.
 */
int findExitPlane() {
	
	// X hits before Y, then compare to Z
	if (t1[c].x < t1[c].y) {
		if (t1[c].x < t1[c].z) {
			return YZ_PLANE;
		} else {
			return XY_PLANE;
		}
	}
	
	// Y hits before X, then compare to Z
	else {
		if (t1[c].y < t1[c].z) {
			return XZ_PLANE;
		} else {
			return XY_PLANE;
		}
	}
}


/**
 * Finds next child ray enters by examining last child and its times.
 */
void findNextChild() {
	
	int exitPlane=findExitPlane();
	
	switch (node[c].name) {
	case 0:
		switch (exitPlane) {
		case XZ_PLANE: updateChild(2); return;
		case YZ_PLANE: updateChild(1); return;
		case XY_PLANE: updateChild(4); return;
		}
	case 1:
		switch (exitPlane) {
		case XZ_PLANE: updateChild(3); return;
		case YZ_PLANE: node[c].name = -1; return;
		case XY_PLANE: updateChild(5); return;
		}
	case 2:
		switch (exitPlane) {
		case XZ_PLANE: node[c].name = -1; return;
		case YZ_PLANE: updateChild(3); return;
		case XY_PLANE: updateChild(6); return;
		}
	case 3:
		switch (exitPlane) {
		case XZ_PLANE: node[c].name = -1; return;
		case YZ_PLANE: node[c].name = -1; return;
		case XY_PLANE: updateChild(7); return;
		}
	case 4:
		switch (exitPlane) {
		case XZ_PLANE: updateChild(6); return;
		case YZ_PLANE: updateChild(5); return;
		case XY_PLANE: node[c].name = -1; return;
		}
	case 5:
		switch (exitPlane) {
		case XZ_PLANE: updateChild(7); return;
		case YZ_PLANE: node[c].name = -1; return;
		case XY_PLANE: node[c].name = -1; return;
		}
	case 6:
		switch (exitPlane) {
		case XZ_PLANE: node[c].name = -1; return;
		case YZ_PLANE: updateChild(7); return;
		case XY_PLANE: node[c].name = -1; return;
		}
	case 7:
		switch (exitPlane) {
		case XZ_PLANE: node[c].name = -1; return;
		case YZ_PLANE: node[c].name = -1; return;
		case XY_PLANE: node[c].name = -1; return;
		}
	}
}


void updateTimes(in float t0x, in float t0y, in float t0z,
                 in float t1x, in float t1y, in float t1z) {
	
	t0[c].x = t0x;
	t0[c].y = t0y;
	t0[c].z = t0z;
	t1[c].x = t1x;
	t1[c].y = t1y;
	t1[c].z = t1z;
}


/**
 * Finds the times of a child node by halving its parent's times.
 */
void updateTimes() {
	
	switch (node[c].name) {
	case 0:
		updateTimes(t0[d].x, t0[d].y, t0[d].z, th[d].x, th[d].y, th[d].z);
		break;
	case 1:
		updateTimes(th[d].x, t0[d].y, t0[d].z, t1[d].x, th[d].y, th[d].z);
		break;
	case 2:
		updateTimes(t0[d].x, th[d].y, t0[d].z, th[d].x, t1[d].y, th[d].z);
		break;
	case 3:
		updateTimes(th[d].x, th[d].y, t0[d].z, t1[d].x, t1[d].y, th[d].z);
		break;
	case 4:
		updateTimes(t0[d].x, t0[d].y, th[d].z, th[d].x, th[d].y, t1[d].z);
		break;
	case 5:
		updateTimes(th[d].x, t0[d].y, th[d].z, t1[d].x, th[d].y, t1[d].z);
		break;
	case 6:
		updateTimes(t0[d].x, th[d].y, th[d].z, th[d].x, t1[d].y, t1[d].z);
		break;
	case 7:
		updateTimes(th[d].x, th[d].y, th[d].z, t1[d].x, t1[d].y, t1[d].z);
		break;
	}
}


void findIntersections(out float tEnter,
                       out float tLeave) {
	
	vec3 tMin, tMax;
	
	// Find min and max
	for (int i=0; i<3; ++i) {
		tMin[i] = min(t0[d][i], t1[d][i]);
		tMax[i] = max(t0[d][i], t1[d][i]);
	}
	
	// Get times where it enters and exits
	tEnter = max(tMin.x, max(tMin.y,tMin.z));
	tLeave = min(tMax.x, min(tMax.y,tMax.z));
}


void sampleAsLeaf() {
	
	float time, timeExit;
	vec4 rayPos, texel;
	
	findIntersections(time, timeExit);
	while (time < timeExit) {
		rayPos = ray.o + (ray.d * time);
		texel = texture(volume, rayPos.stp);
		texel.a = texel.x;
		if (texel.a > 0.01) {
			FragColor = mix(FragColor, texel, texel.a);
			if (FragColor.a > 0.9) {
				break;
			}
		}
		time += 0.1;
	}
}


void sample() {
	
	int step[MAX_HEIGHT];
	
	// Initialize times for root
	t0[0] = vec3((box.lower - ray.o) / ray.d);
	t1[0] = vec3((box.upper - ray.o) / ray.d);
	th[0] = (t0[0] + t1[0]) * 0.5;
	
	// Initialize nodes and steps
	node[0] = OctreeNode(ROOT_KEY, FIRST_CHILD);
	step[0] = SECOND_STEP;
	for (int i=1; i<MAX_HEIGHT; ++i) {
		node[i].name = -1;
		step[i] = FIRST_STEP;
	}
	
	// While in volume
	FragColor = BLACK;
	while (d >= 0) {
		switch (step[d]) {
		case FIRST_STEP:
			
			// If empty skip it and move back up
			if (texelFetch(octree,node[d].key,0).r != uint(0)) {
				--d;
				continue;
			}
			
			// If leaf sample it and move back up
			if (d == height) {
				sampleAsLeaf();
				--d;
				continue;
			}
			
			// Update half times
			th[d] = (t0[d] + t1[d]) * 0.5;
		
		case SECOND_STEP:
			
			// Find first or next child
			c = d + 1;
			if (node[c].name == -1) {
				findEntryChild();
			} else {
				findNextChild();
				if (node[c].name == -1) {
					--d;
					continue;
				}
			}
			
			// Move to child
			updateTimes();
			step[d] = SECOND_STEP;
			step[c] = FIRST_STEP;
			++d;
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


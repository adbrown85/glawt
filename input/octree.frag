/* 
 * octree.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 150
#include "Octree.glsl"
uniform int bufferSize;
uniform sampler2D buffer;
uniform sampler1D octree;
uniform sampler3D volume;
uniform int length;
uniform int height;



void main() {
	
	BoundaryTimes times;
	BoundingBox box;
	OctreeNode root;
	Ray ray;
	
	// Initialize
	Ray_(ray, gl_TexCoord[0], texture2D(buffer,gl_FragCoord.xy/bufferSize));
	BoundingBox_(box);
	OctreeNode_(root, 0, 0);
	
	// Can't handle negative directions yet
	if (Ray_isNegative(ray)) {
		discard;
	}
	
	// Sample
	times = BoundingBox_calculateTimes(box, ray);
	gl_FragColor = Octree_sample(volume, octree, length, ray, root, times, height, 0);
}


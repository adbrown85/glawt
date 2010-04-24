/* 
 * octree.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
#include "Octree.glsl"
uniform sampler2D buffer;
uniform sampler3D volume;
uniform usampler1D octree;
uniform int height;



void main() {
	
	Ray ray;
	
	// Initialize ray
	ray.o = TexCoord;
	ray.d = normalize(texelFetch(buffer,ivec2(gl_FragCoord.xy),0) - TexCoord);
	if (Ray_isNegative(ray)) {
		discard;
	}
	
	// Sample
	Octree_sample(volume, octree, height, ray);
}


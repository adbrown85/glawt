/* 
 * octree.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 110
#include "Octree.glsl"
uniform int bufferSize;
uniform sampler2D buffer;
uniform sampler1D octree;
uniform int count;
uniform sampler3D volume;
uniform int height;



void main() {
	
	Ray ray;
	vec4 rayDir, rayEnd;
	
	// Initialize
	rayEnd = texture2D(buffer, gl_FragCoord.xy/float(bufferSize));
	rayDir = rayEnd - gl_TexCoord[0];
	ray = Ray(gl_TexCoord[0], rayDir);
	
	// Can't handle negative directions yet
	if (Ray_isNegative(ray)) {
		discard;
	}
	
	// Sample
	Octree_sample(volume, octree, count, ray, height);
}


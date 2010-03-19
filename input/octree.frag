/* 
 * octree.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Octree.glsl"
uniform int bufferSize;
uniform sampler2D buffer;
uniform sampler1D octree;
uniform sampler3D volume;
uniform int length;
uniform int height;



void main() {
	
	Ray ray;
	vec4 rayEnd;
	
	// Initialize
	rayEnd = texture2D(buffer, gl_FragCoord.xy/float(bufferSize));
	Ray_(ray, gl_TexCoord[0], rayEnd);
	
	// Can't handle negative directions yet
	if (Ray_isNegative(ray)) {
		discard;
	}
	
	// Sample
	gl_FragColor = Octree_sample(volume, octree, length, ray, height);
}


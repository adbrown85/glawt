/*
 * Octree.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
#include "../../input/Colors.glsl"
uniform usampler1D octree;
in vec3 TexCoord;
out vec4 FragColor;


bool isAtEdge() {
	
	return TexCoord.s < 0.01 || TexCoord.s > 0.99 ||
	       TexCoord.t < 0.01 || TexCoord.t > 0.99;
}


void main() {
	
	uvec4 texel;
	
	if (isAtEdge()) {
		FragColor = YELLOW;
	} else {
		texel = texelFetch(octree, 8, 0);
		if (texel.x == uint(0)) {
			FragColor = GREEN;
		} else {
			FragColor = RED;
		}
	}
}


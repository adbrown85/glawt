/*
 * outline.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
#include "Colors.glsl"
out vec4 FragColor;


void main() {
	
	gl_FragDepth = gl_FragCoord.z - 0.0001;
	FragColor = YELLOW;
}


/*
 * texture-size.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
#include "Colors.glsl"
uniform sampler2D unit;
out vec4 FragColor;


void main() {
	
	if (textureSize(unit,0).x == 256) {
		FragColor = GREEN;
	} else {
		FragColor = RED;
	}
}


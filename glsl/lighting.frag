/*
 * lighting.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
#include "Colors.glsl"
uniform vec4 Color=vec4(1,1,1,1);
in float LightIntensity;
out vec4 FragColor;


void main() {
	
	FragColor = Color * LightIntensity;
}


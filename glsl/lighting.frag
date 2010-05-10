/*
 * lighting.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
#include "Colors.glsl"
in float LightIntensity;
out vec4 FragColor;


void main() {
	
	FragColor = vec4(vec3(LightIntensity),1.0);
}


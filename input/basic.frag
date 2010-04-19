/*
 * basic.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
#include "Colors.glsl"
in vec3 TexCoord;
in float LightIntensity;
out vec4 FragColor;


void main() {
	
	//fragColor = BLUE;
	FragColor = vec4(TexCoord,1.0) * vec4(vec3(LightIntensity),1.0);
}


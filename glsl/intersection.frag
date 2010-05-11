/*
 * intersection.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

// Uniforms
uniform vec4 Color0;
uniform vec4 Color1;
uniform sampler3D Texture0;
uniform sampler3D Texture1;

// Input
in vec3 Coord0;
in vec3 Coord1;

// Output
out vec4 FragColor;


void main() {
	
	FragColor = vec4(1,1,1,1);
}


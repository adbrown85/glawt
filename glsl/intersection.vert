/*
 * intersection.vert
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

// Uniforms
uniform mat4 MVPMatrix;

// Input
in vec4 MCVertex;
in vec3 TexCoord0;
in vec3 TexCoord1;

// Output
out vec3 Coord0;
out vec3 Coord1;


void main() {
	
	Coord0 = TexCoord0;
	Coord1 = TexCoord1;
	gl_Position = MVPMatrix * MCVertex;
}


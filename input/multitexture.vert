/*
 * multitexture.vert
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
uniform mat4 MVPMatrix;
in vec4 MCVertex;
in vec3 TexCoord0;
out vec3 TexCoord;


void main() {
	
	// Computations
	TexCoord = TexCoord0;
	gl_Position = MVPMatrix * MCVertex;
}


/*
 * coordinates.vert
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
uniform mat4 MVPMatrix;
in vec4 MCVertex;
in vec3 TexCoord0;
out vec3 TexCoord;
invariant gl_Position;


void main() {
	
	TexCoord = TexCoord0;
	gl_Position = MVPMatrix * MCVertex;
}


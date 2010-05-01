/*
 * halfmoon.vert
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
uniform mat4 MVPMatrix;
in vec4 MCVertex;
in vec2 TexCoord0;
out vec2 TexCoord;


void main() {
	
	TexCoord = TexCoord0;
	gl_Position = MVPMatrix * MCVertex;
}


/*
 * octree.vert
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
uniform mat4 MVPMatrix;
in vec4 MCVertex;
in vec4 TexCoord0;
out vec4 TexCoord;
//invariant gl_Position;


void main() {
	
	TexCoord = TexCoord0;
	gl_Position = MVPMatrix * MCVertex;
}


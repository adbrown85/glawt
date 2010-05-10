/*
 * normals.vert
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
uniform mat4 MVPMatrix;
in vec4 MCVertex;
in vec4 MCNormal;
out vec4 Color;


void main() {
	
	Color = MCNormal;
	gl_Position = MVPMatrix * MCVertex;
}


/*
 * texture-size.vert
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
uniform mat4 MVPMatrix;
in vec4 MCVertex;


void main() {
	
	gl_Position = MVPMatrix * MCVertex;
}


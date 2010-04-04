/*
 * basic.vert
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
uniform mat4 mvpMatrix;
in vec4 mcVertex;


void main() {
	
	gl_Position = mvpMatrix * mcVertex;
/*
	gl_Position = gl_ModelViewProjectionMatrix * mcVertex;
*/
}


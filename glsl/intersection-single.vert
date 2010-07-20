/*
 * intersection-single.vert
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

/* Uniforms */
uniform mat4 MVPMatrix;

/* Inputs */
in vec4 MCVertex;


/** Sets the position. */
void main() {
	
	gl_Position = MVPMatrix * MCVertex;
}


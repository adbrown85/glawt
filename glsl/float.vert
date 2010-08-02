/*
 * float.vert
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

/* Uniforms */
uniform mat4 MVPMatrix;
uniform mat4 MVMatrix;

/* Inputs */
in vec4 MCVertex;

/* Outputs */
out vec3 MVPosition;


/** Compute vertex position. */
void main() {
	
	MVPosition = (MVMatrix * MCVertex).xyz;
	gl_Position = MVPMatrix * MCVertex;
}


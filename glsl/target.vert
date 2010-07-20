/*
 * target.vert
 * 
 * Author
 *     Andrew Brown
 */
#version 130

/* Uniforms */
uniform mat4 MVPMatrix;

/* Inputs */
in vec4 MCVertex;


/** Set the vertex position. */
void main() {
	
	gl_Position = MVPMatrix * MCVertex;
}


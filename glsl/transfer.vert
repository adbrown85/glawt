/*
 * transfer.vert
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

/* Uniforms */
uniform mat4 MVPMatrix;

/* Inputs */
in vec4 MCVertex;
in vec4 TexCoord0;

/* Outputs */
out vec3 Coord;
invariant gl_Position;


/** Computes the vertex position and texture coordinates. */
void main() {
	
	gl_Position = MVPMatrix * MCVertex;
	Coord = TexCoord0.stp;
}


/*
 * intersection-single-coords.vert
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
in vec3 TexCoord0;

/* Outputs */
out vec3 Coord0;
out vec3 MVPosition;
invariant out vec4 gl_Position;


/** Pass texture coordinates and position to next stage. */
void main() {
	
	Coord0 = TexCoord0;
	MVPosition = (MVMatrix * MCVertex).xyz;
	gl_Position = MVPMatrix * MCVertex;
}


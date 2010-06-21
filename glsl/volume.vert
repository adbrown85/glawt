/*
 * volume.vert
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

/* Uniforms */
uniform mat4 MVPMatrix;

/* Inputs */
in vec4 MCVertex;
in vec3 TexCoord0;

/* Outputs */
out vec3 Origin;
//invariant gl_Position;


/** Sets the position and texture coordinates. */
void main() {
	
	gl_Position = MVPMatrix * MCVertex;
	Origin = TexCoord0;
}


/*
 * intersection.vert
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

/* Uniforms */
uniform mat4 MVPMatrix;

/* Input */
in vec4 MCVertex;
in vec3 TexCoord0;
in vec3 TexCoord1;

/* Output */
out vec3 Origin0;
out vec3 Origin1;


/** Assigns the coordinates and position. */
void main() {
	
	// Coordinates
	Origin0 = TexCoord0;
	Origin1 = TexCoord1;
	
	// Position
	gl_Position = MVPMatrix * MCVertex;
}


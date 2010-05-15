/*
 * coordinates.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

// Uniforms
uniform int which;

// Inputs
in vec3 Coord0;
in vec3 Coord1;

// Outputs
out vec4 FragColor;


void main() {
	
	if (which == 0) {
		FragColor = vec4(Coord0, 1.0);
	} else {
		FragColor = vec4(Coord1, 1.0);
	}
}


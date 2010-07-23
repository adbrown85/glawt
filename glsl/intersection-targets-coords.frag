/*
 * intersection-targets-coords.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

/* Uniforms */
uniform int Which;

/* Inputs */
in vec3 Coord0;
in vec3 MVPosition;

/* Outputs */
out vec4 Target0;
out vec4 Target1;


/** Output coordinates to one of the targets. */
void main() {
	
	float depth;
	
	depth = (MVPosition.z - 0.8) / 14.2;
	
	if (Which == 0) {
		Target0 = vec4(Coord0, -depth);
	} else {
		Target1 = vec4(Coord0, -depth);
	}
}


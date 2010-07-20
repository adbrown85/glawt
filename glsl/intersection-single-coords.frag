/*
 * intersection-single-coords.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

/* Uniforms */
uniform int Which;

/* Inputs */
in vec3 Coord0;

/* Outputs */
out vec4 Target0;
out vec4 Target1;


/** Output coordinates to one of the targets. */
void main() {
	
	if (Which == 0) {
		Target0 = vec4(Coord0, gl_FragCoord.z);
	} else {
		Target1 = vec4(Coord0, gl_FragCoord.z);
	}
}


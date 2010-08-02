/*
 * float-results.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
#include "Colors.glsl"
#include "Target.glsl"

/* Uniforms */
uniform sampler2D MVPositionTarget;

/* Outputs */
out vec4 FragColor;


void main() {
	
	vec4 MVPosition;
	
	MVPosition = Target_getValue(MVPositionTarget);
	if (MVPosition.z < -7.9) {
		FragColor = GREEN;
	} else {
		FragColor = RED;
	}
}


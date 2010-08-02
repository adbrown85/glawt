/*
 * float.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

/* Inputs */
in vec3 MVPosition;

/* Outputs */
out vec4 FragColor;


/** Compute fragment color. */
void main() {
	
	FragColor = vec4(MVPosition,1);
}


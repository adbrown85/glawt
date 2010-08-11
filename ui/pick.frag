/*
 * pick.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

/* Uniforms */
uniform int ItemID;
uniform int SourceID;

/* Outputs */
out vec4 FragColor;


/** Compute fragment color. */
void main() {
	
	FragColor = vec4(ItemID, SourceID, 0, 1);
}


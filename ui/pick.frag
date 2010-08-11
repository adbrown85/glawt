/*
 * pick.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

/* Uniforms */
uniform int DrawableID;
uniform int ParentID;

/* Outputs */
out vec4 FragColor;


/** Compute fragment color. */
void main() {
	
	FragColor = vec4(DrawableID, ParentID, 0, 1);
}


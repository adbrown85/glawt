/*
 * shadow-cast.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

/* Outputs */
out vec4 FragColor;


/** Compute fragment color. */
void main() {
	
	FragColor.rgb = vec3(gl_FragCoord.z);
	FragColor.a = 1.0;
}


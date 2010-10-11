/*
 * UniformFloatArray.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

/* Uniforms */
uniform float Values[6];

/* Outputs */
out vec4 FragColor;


/** Compute fragment color. */
void main() {
	
	FragColor.rgb = vec3(Values[2]);
	FragColor.a = 1.0;
}


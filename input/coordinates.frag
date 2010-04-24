/*
 * coordinates.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
in vec3 TexCoord;
out vec4 FragColor;


void main() {
	
	FragColor = vec4(TexCoord, 1.0);
}


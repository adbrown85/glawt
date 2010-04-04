/*
 * coordinates.frag
 *     Sets the fragment equal to its coordinates.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#version 130
in vec3 texCoord;
out vec4 fragColor;



void main() {
	
	fragColor = vec4(texCoord, 1.0);
}


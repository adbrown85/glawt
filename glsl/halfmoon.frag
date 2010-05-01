/*
 * halfmoon.frag
 *     Colors half an object dark and the other light.
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
in vec2 TexCoord;
out vec4 FragColor;


void main() {
	
	if (TexCoord.s < 0.5)
		FragColor = vec4(0.15, 0.15, 0.15, 1.00);
	else
		FragColor = vec4(1.00, 1.00, 1.00, 0.90);
}


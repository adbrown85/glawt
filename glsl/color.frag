/*
 * color.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
uniform vec4 Color=vec4(1,1,1,1);
out vec4 FragColor;


void main() {
	
	FragColor = Color;
}


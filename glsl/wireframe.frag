/*
 * wireframe.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
uniform vec4 Color;
out vec4 FragColor;


void main() {
	
	gl_FragDepth = gl_FragCoord.z - 0.0001;
	FragColor = Color;
}


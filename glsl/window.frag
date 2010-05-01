/*
 * window.frag
 * 
 * Author
 *     Andrew Brown
 */
#version 130
uniform int WindowSize;
in vec2 TexCoord;
out vec4 FragColor;


void main() {
	
	FragColor.rg = gl_FragCoord.xy / WindowSize;
	FragColor.a = 1.0;
}


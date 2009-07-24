/*
 * halfmoon.glsl
 *     Colors half an object dark and the other light.
 */


void main() {
	
	if (gl_TexCoord[0].s < 0.5)
		gl_FragColor = 0.15;
	else
		gl_FragColor = 0.95;
}

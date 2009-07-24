/*
 * halfmoon-vars.glsl
 *     Colors half an object dark and the other light.
 */
uniform float brightness;


void main() {
	
	if (gl_TexCoord[0].s < 0.5)
		gl_FragColor = 0.15 * brightness;
	else
		gl_FragColor = 0.95 * brightness;
}

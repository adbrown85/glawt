/*
 * halfmoon.frag
 *     Colors half an object dark and the other light.
 */


void main() {
	
	if (gl_TexCoord[0].s < 0.5)
		gl_FragColor = vec4(0.15, 0.15, 0.15, 1.00);
	else
		gl_FragColor = vec4(1.00, 1.00, 1.00, 0.90);
}


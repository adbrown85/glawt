/*
 * coordinates.frag
 *     Sets a fragment's color as its texture coordinates.
 */


void main() {
	
	gl_FragColor = gl_TexCoord[0];
}

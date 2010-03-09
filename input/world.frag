/*
 * world.frag
 *     Shows off world coordinates.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
varying vec4 vertexPosition;



void main() {
	
	/* Set fragment color to world coordinates */
	gl_FragColor = normalize(vertexPosition);
	gl_FragColor.a = 1.0;
}


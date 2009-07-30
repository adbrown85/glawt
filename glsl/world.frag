/*
 * world.frag
 *     Shows off world coordinates.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
varying vec4 vertexPosition;



void main() {
	
	vec4 worldPosition;
	
	/* Set fragment color to world coordinates */
	worldPosition = normalize(vertexPosition * gl_ModelViewMatrix);
	gl_FragColor = worldPosition;
}

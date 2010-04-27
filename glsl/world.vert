/*
 * world.vert
 *     Shows off world coordinates.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
varying vec4 vertexPosition;



void main() {
	
	/* Set coordinates and position */
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = ftransform();
	vertexPosition = gl_Position;
}


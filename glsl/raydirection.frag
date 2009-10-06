/*
 * raydirection.frag
 *     Visualizes ray direction.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
uniform int width, height;
varying vec4 vertexPosition;



void main() {
	
	vec4 direction;
	vec4 red=vec4(1.0, 0.0, 0.0, 1.0),
	     green=vec4(0.0, 1.0, 0.0, 1.0),
	     blue=vec4(0.0, 0.0, 1.0, 1.0),
	     yellow=vec4(1.0, 1.0, 0.0, 1.0);
	
	/* Set direction */
	direction = gl_ModelViewMatrix * gl_TexCoord[0];
	direction.z = 1.0;
	
	/* Visualize colors */
	if (direction.x < 0)
		gl_FragColor = red;
	else
		gl_FragColor = green;
	if (direction.y > +0.5)
		gl_FragColor = blue;
	else if (direction.y < -0.5)
		gl_FragColor = yellow;
}


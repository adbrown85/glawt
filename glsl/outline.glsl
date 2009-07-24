/*
 * outline.glsl
 *     Colors the edges of an object yellow.
 */


void main() {
	
	float s = gl_TexCoord[0].s;
	float t = gl_TexCoord[0].t;
	float p = gl_TexCoord[0].p;
	int count = 0;
	
	/* Determine if near edge */
	if (s < 0.05 || s > 0.95)
		count++;
	if (t < 0.05 || t > 0.95)
		count++;
	if (p < 0.05 || p > 0.95)
		count++;
	
	/* Use different color if near edge */
	if (count >= 2)
		gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
	else
		gl_FragColor = gl_TexCoord[0];
}

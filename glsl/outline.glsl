uniform sampler2D unit0, unit1;


void main() {
	
	float s = gl_TexCoord[0].s;
	float t = gl_TexCoord[0].t;
	float p = gl_TexCoord[0].p;
	int count = 0;
	
	/* Determine if near edge */
	if (s < 0.1 || s > 0.9)
		count++;
	if (t < 0.1 || t > 0.9)
		count++;
	if (p < 0.1 || p > 0.9)
		count++;
	
	/* Use different color if near edge */
	if (count >= 2)
		gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
	else
		gl_FragColor = gl_TexCoord[0];
}

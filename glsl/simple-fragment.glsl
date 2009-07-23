uniform sampler2D unit0, unit1;


void main() {
	
	float s = gl_TexCoord[0].s;
	
	if (s < 0.5)
		gl_FragColor = texture2D(unit0, gl_TexCoord[0].st);
	else
		gl_FragColor = texture2D(unit1, gl_TexCoord[0].st);
}

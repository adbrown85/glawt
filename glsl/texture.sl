uniform sampler2D unit0, unit1;


void main() {
	
	gl_FragColor = texture2D(unit0, gl_TexCoord[0].st);
}

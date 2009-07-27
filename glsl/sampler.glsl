uniform sampler2D primary;


void main() {
	
	gl_FragColor = texture2D(primary, gl_TexCoord[0].st);
}

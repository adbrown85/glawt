uniform float brightness;


void main() {
	
	gl_FragColor = gl_TexCoord[0] * brightness;
}

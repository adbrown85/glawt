uniform sampler3D volume;


void main() {
	
	vec4 sample = texture3D(volume, gl_TexCoord[0].stp);
	gl_FragColor = sample;
}

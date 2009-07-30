uniform sampler3D volume;


void main() {
	
	vec3 position;
	vec4 total=0;
	
	/* Build up color */
	position = gl_TexCoord[0];
	for (int i=0; i<10; ++i) {
		position.p = i * 0.1;
		total += texture3D(volume, position) * 0.1;
	}
	
	/* Set as fragment color */
	gl_FragColor = total;
}

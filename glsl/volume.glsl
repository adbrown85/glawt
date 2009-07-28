uniform sampler3D volume;


void main() {
	
	float s, t, p;
	s = gl_TexCoord[0].s;
	t = gl_TexCoord[0].t;
	p = 0.5;
	vec3 pos = vec3(s, t, p);
	gl_FragColor = texture3D(volume, pos);
}

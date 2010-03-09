/*
 * kruger.frag
 * 
 * Author
 *     Andrew Brown
 */
uniform sampler2D target;
uniform sampler3D volume;
uniform int samples;



void main() {
	
	int steps;
	vec4 rayDir, rayEnd, rayInc, rayPos, sample;
	
	/* Form ray */
	rayEnd = texture2D(target, gl_FragCoord.xy / 512);
	rayPos = gl_TexCoord[0];
	rayDir = normalize(rayEnd - rayPos);
	rayInc = rayDir * (1.732 / samples);
	steps = length(rayEnd - rayPos) / length(rayInc);
	
	/* Sample through volume */
	for (int i=0; i<steps; ++i) {
		rayPos += rayInc;
		sample = texture3D(volume, rayPos.stp);
		sample.a = sample.x;
		if (sample.a > 0.01) {
			gl_FragColor = mix(gl_FragColor, sample, sample.a);
			if (gl_FragColor.a > 0.9)
				break;
		}
	}
}


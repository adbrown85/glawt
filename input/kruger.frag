/*
 * kruger.frag
 * 
 * Author
 *     Andrew Brown
 */
#version 130
uniform sampler2D target;
uniform sampler3D volume;
uniform int samples;
in vec4 TexCoord;
out vec4 FragColor;



void main() {
	
	int steps;
	vec4 rayDir, rayEnd, rayInc, rayPos, sample;
	
	// Form ray
	rayEnd = texelFetch(target, ivec2(gl_FragCoord.xy), 0);
	rayPos = TexCoord;
	rayDir = normalize(rayEnd - rayPos);
	rayInc = rayDir * (1.732 / samples);
	
	// Sample through volume
	steps = int(length(rayEnd-rayPos) / length(rayInc));
	for (int i=0; i<steps; ++i) {
		rayPos += rayInc;
		sample = texture(volume, rayPos.stp);
		sample.a = sample.x;
		if (sample.a > 0.01) {
			FragColor = mix(FragColor, sample, sample.a);
			if (FragColor.a > 0.9)
				break;
		}
	}
}


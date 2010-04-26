/*
 * kruger.frag
 * 
 * Author
 *     Andrew Brown
 */
#version 130
#include "Colors.glsl"
#include "Ray.glsl"

// Uniforms
uniform sampler2D target;
uniform sampler3D volume;
uniform int samples;

// Inputs and outputs
in vec4 TexCoord;
out vec4 FragColor;


void main() {
	
	float t, tExit;
	Ray ray;
	vec4 exit, pos, sample, times;
	
	// Initialize
	exit = texelFetch(target, ivec2(gl_FragCoord.xy), 0);
	ray.o = TexCoord;
	ray.d = normalize(exit - TexCoord);
	times = (exit - ray.o) / ray.d;
	tExit = min(times.x, min(times.y, times.z));
	
	// Sample until out of volume
	FragColor = BLACK;
	while (t < tExit) {
		pos = ray.o + (ray.d * t);
		sample = texture(volume, pos.stp);
		sample.a = sample.x;
		if (sample.a > 0.3) {
			FragColor = mix(FragColor, sample, sample.a);
			if (FragColor.a > 0.9)
				break;
		}
		t += 0.02;
	}
}


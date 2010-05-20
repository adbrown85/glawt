/*
 * volume.frag
 * 
 * Author
 *     Andrew Brown
 */
#version 130
#include "Colors.glsl"
#include "Ray.glsl"

/* Uniforms */
uniform int WindowSize;
uniform float SampleRate;
uniform sampler2D ExitCoords;
uniform sampler3D Volume;

/* Inputs and outputs */
in vec3 Origin;
out vec4 FragColor;


void main() {
	
	float t, tExit;
	vec3 d, exit, times;
	vec4 sample;
	
	// Initialize direction and times
	exit = (texture(ExitCoords, gl_FragCoord.xy/WindowSize)).xyz;
	d = normalize(exit - Origin);
	times = (exit - Origin) / d;
	tExit = min(times.x, min(times.y, times.z));
	
	// Sample until out of volume
	FragColor = vec4(0,0,0,0);
	t = 0.0;
	while (t < tExit) {
		sample = texture(Volume, Origin+(d*t));
		sample.a = sample.x; /* * Transfer */
		//if (sample.a > 0.1) {
			FragColor = mix(FragColor, sample, sample.a);
		//}
		t += SampleRate;
	}
}


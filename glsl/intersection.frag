/*
 * intersection.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
#include "Colors.glsl"
#include "Ray.glsl"

/* Uniforms */
uniform int WindowSize;
uniform float SampleRate;
uniform float Transfer;
uniform sampler2D EndCoords0;
uniform sampler2D EndCoords1;
uniform sampler3D Volume0;
uniform sampler3D Volume1;
uniform vec4 Color0;
uniform vec4 Color1;

/* Inputs */
in vec3 Origin0;
in vec3 Origin1;

/* Outputs */
out vec4 FragColor;


/** Samples the volumes from front face to back face. */
void main() {
	
	float t, tExit;
	vec3 d, exit, times;
	vec4 sample;
	
	// Initialize direction and times
	exit = (texture(EndCoords0, gl_FragCoord.xy/WindowSize)).xyz;
	d = normalize(exit - Origin0);
	times = (exit - Origin0) / d;
	tExit = min(times.x, min(times.y, times.z));
	
	// Sample until out of volume
	FragColor = vec4(0,0,0,0);
	t = 0.0;
	while (t < tExit) {
		sample = texture(Volume0, Origin0+(d*t));
		sample.a = sample.x * Transfer;
		sample *= vec4(Color0.rgb,1.0);
		if (sample.a > 0.1) {
			FragColor = mix(FragColor, sample, sample.a);
		}
		sample = texture(Volume1, Origin1+(d*t));
		sample.a = sample.x * 0.5;
		sample *= vec4(Color1.rgb,1.0);
		if (sample.a > 0.1) {
			FragColor = mix(FragColor, sample, sample.a);
		}
		t += SampleRate;
	}
}

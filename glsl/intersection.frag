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
uniform int CanvasSize=512;
uniform float SampleRate=0.01;
uniform float Brightness=1.0;
uniform vec3[5] Colors=vec3[5](BLUE,GREEN,YELLOW,ORANGE,RED);
uniform float[5] Transfer=float[5](0.2, 0.3, 0.4, 0.6, 0.8);
uniform float Opacity=1.0;
uniform sampler2D Results;
uniform sampler2D EndCoords0;
//uniform sampler2D EndCoords1;
uniform sampler3D Volume0;
uniform sampler3D Volume1;

/* Inputs */
in vec3 Origin0;
in vec3 Origin1;

/* Outputs */
out vec4 FragColor;


vec3 transfer(float value) {
	
	if (value < Transfer[0]) {
		return Colors[0];
	}
	for (int i=1; i<4; ++i) {
		if (value < Transfer[i]) {
			value = smoothstep(Transfer[i-1], Transfer[i], value);
			return mix(Colors[i-1], Colors[i], value);
		}
	}
	return Colors[4];
}


/** Samples the volumes from back face to front face. */
void main() {
	
	float t, tExit;
	vec3 d, exit, times;
	vec4 sample;
	
	// Initialize direction and times
	exit = (texture(EndCoords0, gl_FragCoord.xy/CanvasSize)).xyz;
	d = normalize(exit - Origin0);
	times = (exit - Origin0) / d;
	tExit = min(times.x, min(times.y, times.z));
	
	// Sample until out of volume
	FragColor = texture(Results, gl_FragCoord.xy/CanvasSize);
	t = 0.0;
	while (t < tExit) {
		sample.a = texture(Volume0, Origin0+(d*t)).x;
		sample.xyz = transfer(sample.a);
		if (sample.a > 0.1) {
			FragColor = mix(FragColor, sample, sample.a);
		}
		sample.a = texture(Volume1, Origin1+(d*t)).x;
		sample.xyz = transfer(sample.a);
		if (sample.a > 0.1) {
			FragColor = mix(FragColor, sample, sample.a);
		}
		t += SampleRate;
	}
}


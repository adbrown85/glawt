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
uniform int WindowSize=512;
uniform float SampleRate=0.006;
uniform float Brightness=1.0;
uniform vec3[5] Colors=vec3[5](BLUE,GREEN,YELLOW,ORANGE,RED);
uniform float[5] Transfer=float[5](0.2, 0.3, 0.4, 0.6, 0.8);
uniform float Opacity=2.0;
uniform sampler2D ExitCoords;
uniform sampler3D Volume;

/* Inputs and outputs */
in vec3 Origin;
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
	t = SampleRate;
	while (t < tExit) {
		sample = texture(Volume, Origin+(d*t));
		sample.a = sample.x;
		sample.xyz = transfer(sample.a) * Brightness;
		if (sample.a > 0.1) {
			FragColor = mix(FragColor, sample, sample.a);
		}
		t += SampleRate;
	}
	FragColor.a *= Opacity;
	
	// Fix opacity
	if (FragColor.a > 0.1) {
		FragColor.a = 1.0;
	} else {
		FragColor.a = 0.0;
	}
}


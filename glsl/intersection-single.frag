/*
 * intersection-single.frag
 * 
 * Author
 *     Andrew Brown
 */
#version 130
#include "Colors.glsl"
#include "Ray.glsl"

/* Uniforms */
uniform int CanvasSize=512;
uniform float SampleRate=0.01;
uniform int Which;
uniform sampler2D Back[2];
uniform sampler2D Front[2];
uniform sampler3D Volume[2];

/* Outputs */
out vec4 FragColor;

/* Globals */
float bDepth[2], fDepth[2];
vec3 bCoord[2], fCoord[2];


/** Retrieve a stored value from a render target. */
vec4 getFromTarget(sampler2D target) {
	
	return texture(target, gl_FragCoord.xy/CanvasSize);
}


/** Initialize coordinates and depths. */
void initialize() {
	
	vec4 value;
	
	// Retrieve coordinates and depths
	for (int i=0; i<2; ++i) {
		value = getFromTarget(Back[i]);
		bCoord[i] = value.xyz;
		bDepth[i] = value.a;
		value = getFromTarget(Front[i]);
		fCoord[i] = value.xyz;
		fDepth[i] = value.a;
	}
	
	// Output
	FragColor = vec4(0,0,0,0);
}


/** Render a volume. */
void render_volume(sampler3D volume, vec3 origin, vec3 exit) {
	
	float t, tExit;
	vec3 d, times;
	vec4 sample;
	
	// Initialize direction and times
	d = normalize(exit - origin);
	times = (exit - origin) / d;
	tExit = min(times.x, min(times.y, times.z));
	
	// Sample until out of volume
	t = SampleRate;
	while (t < tExit) {
		sample.a = texture(volume, origin+(d*t)).x;
		sample.rgb = vec3(sample.a);
		if (sample.a > 0.1) {
			FragColor = mix(FragColor, sample, sample.a);
		}
		t += SampleRate;
	}
}


/** Convenience for rendering a volume. */
void render_volume(int i) {
	
	render_volume(Volume[i], bCoord[i], fCoord[i]);
}


/** Convenience for rendering a volume. */
void render_volume() {
	
	switch (Which) {
	case 0: render_volume(0); break;
	case 1: render_volume(1); break;
	}
}


int getOther() {
	
	switch (Which) {
	case 0: return 1;
	case 1: return 0;
	}
}


bool is_only_volume_at_pixel() {
	
	int other;
	
	other = getOther();
	return ((bDepth[other] < 0.01) && (fDepth[other] < 0.01));
}


bool is_separated() {
	
	int other=getOther();
	
	if (bDepth[Which] < fDepth[other]) {
		return true;
	} else if (fDepth[Which] > bDepth[other]) {
		return true;
	} else {
		return false;
	}
}


/** Main program. */
void main() {
	
	// Initialize
	initialize();
	
	// Render
	if (is_only_volume_at_pixel() || is_separated()) {
		render_volume();
	} else {
		FragColor = RED;
	}
}


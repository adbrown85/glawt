/*
 * intersection-single.frag
 * 
 * Author
 *     Andrew Brown
 */
#version 130
#include "Colors.glsl"
#include "Ray.glsl"
#include "Volume.glsl"
#include "Target.glsl"

/* Uniforms */
uniform int Which;
uniform sampler2D Back0;
uniform sampler2D Back1;
uniform sampler2D Front0;
uniform sampler2D Front1;
uniform sampler3D Volume0;
uniform sampler3D Volume1;

/* Globals */
float bDepth0, bDepth1, fDepth0, fDepth1;
vec3 bCoord0, bCoord1, fCoord0, fCoord1;
Ray ray0, ray1;


/** Initialize coordinates and depths. */
void initialize() {
	
	vec4 value;
	
	// Retrieve coordinates and depths
	value = Target_getValue(Back0);
	bCoord0 = value.xyz;
	bDepth0 = value.a;
	value = Target_getValue(Front0);
	fCoord0 = value.xyz;
	fDepth0 = value.a;
	value = Target_getValue(Back1);
	bCoord1 = value.xyz;
	bDepth1 = value.a;
	value = Target_getValue(Front1);
	fCoord1 = value.xyz;
	fDepth1 = value.a;
	
	// Rays
	ray0 = Ray_construct(bCoord0, fCoord0);
	ray1 = Ray_construct(bCoord1, fCoord1);
	
	// Output
	FragColor = vec4(0,0,0,0);
}


/** Convenience for rendering this volume. */
void render_this_volume(float start, float stop) {
	
	switch (Which) {
	case 0: Volume_render(Volume0, ray0, start, stop); break;
	case 1: Volume_render(Volume1, ray1, start, stop); break;
	}
}


/** Convenience for rendering other volume. */
void render_other_volume(float start, float stop) {
	
	switch (Which) {
	case 0: Volume_render(Volume1, ray1, start, stop); break;
	case 1: Volume_render(Volume0, ray0, start, stop); break;
	}
}


/** Convenience for rendering both volumes. */
void render_both_volumes(float startA, float stopA,
                         float startB, float stopB) {
	
	switch (Which) {
	case 0: Volume_render_two(Volume0, ray0, Volume1, ray1,
	                          startA, stopA, startB, stopB);
	case 1: Volume_render_two(Volume1, ray1, Volume0, ray0,
	                          startA, stopA, startB, stopB);
	}
}


bool is_only_volume_at_pixel() {
	
	switch (Which) {
	case 0: return ((bDepth1 < 0.01) && (fDepth1 < 0.01));
	case 1: return ((bDepth0 < 0.01) && (fDepth0 < 0.01));
	}
}


bool is_completely_in_front() {
	
	switch (Which) {
	case 0: return bDepth0 <= fDepth1;
	case 1: return bDepth1 < fDepth0;
	}
}


bool is_completely_behind() {
	
	switch (Which) {
	case 0: return fDepth0 > bDepth1;
	case 1: return fDepth1 >= bDepth0;
	}
}


bool is_in_front() {
	
	switch (Which) {
	case 0: return fDepth0 < fDepth1;
	case 1: return fDepth1 < fDepth0;
	}
}


bool is_separated() {
	
	return is_only_volume_at_pixel()
	         || is_completely_in_front()
	         || is_completely_behind();
}


float find_percent_past_overlap() {
	
	switch (Which) {
	case 0: return (bDepth0 - fDepth1) / (bDepth0 - fDepth0);
	case 1: return (bDepth1 - fDepth0) / (bDepth1 - fDepth1);
	}
}


float find_percent_to_overlap() {
	
	switch (Which) {
	case 0: return (bDepth1 - bDepth0) / (bDepth1 - fDepth1);
	case 1: return (bDepth0 - bDepth1) / (bDepth0 - fDepth0);
	}
}


void render_all() {
	
	float pPastOverlap, pToOverlap;
	
	// Find percents
	pToOverlap = find_percent_to_overlap();
	pPastOverlap = find_percent_past_overlap();
	
	// Render
	render_other_volume(0.0, pToOverlap);
	//render_this_volume(0.0, pPastOverlap);
	//render_other_volume(pToOverlap, 1.0);
	render_both_volumes(0.0, pPastOverlap, pToOverlap, 1.0);
	render_this_volume(pPastOverlap, 1.0);
}


/** Main program. */
void main() {
	
	// Initialize
	initialize();
	
	// Render
	if (is_separated()) {
		render_this_volume(0.0, 1.0);
	} else if (is_in_front()) {
		render_all();
	} else {
		discard;
	}
	
	// Check alpha
	if (FragColor.a == 0) {
		discard;
	}
}


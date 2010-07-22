/*
 * intersection.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
#include "Colors.glsl"
#include "Ray.glsl"
#include "Volume.glsl"
#include "Target.glsl"

/* Uniforms */
uniform sampler2D Results;
uniform sampler2D EndCoords0;
uniform sampler2D EndCoords1;
uniform sampler3D Volume0;
uniform sampler3D Volume1;

/* Inputs */
in vec3 Origin0;
in vec3 Origin1;


/** Samples the volumes from back face to front face. */
void main() {
	
	//float t;
	Ray ray0, ray1;
	
	// Initialize ray
	ray0 = Ray_construct(Origin0, Target_getValue(EndCoords0).xyz);
	ray1.o = Origin1;
	ray1.d = ray0.d;
	
	// Initialize color
	FragColor = Target_getValue(Results);
	
	// Sample until out of volume
	Volume_render_two(Volume0, ray0, 0, 1, Volume1, ray1, 0, 1);
}


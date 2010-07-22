/*
 * volume.frag
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
uniform sampler2D Results;
uniform sampler2D ExitCoords;
uniform sampler3D Volume;

/* Inputs */
in vec3 Origin;


void main() {
	
	Ray ray;
	
	// Initialize ray
	ray = Ray_construct(Origin, Target_getValue(ExitCoords).xyz);
	
	// Initialize color
	FragColor = Target_getValue(Results);
	
	// Sample until out of volume
	Volume_render(Volume, ray, 0.0, 1.0);
}


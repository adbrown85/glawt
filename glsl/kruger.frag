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
uniform sampler2D Target;
uniform sampler3D Volume;
uniform vec3 LightDirection;
uniform float Ambient, Diffuse;

// Inputs and outputs
in vec4 TexCoord;
out vec4 FragColor;

// Globals
float Pitch;
vec3 Normal;


/**
 * Computes the normal vector for a sample.
 * 
 * @param p Position in local coordinates.
 */
void findNormal(in vec4 p) {
	
	vec3 g;
	
	// Find gradient by central difference
	g.x = (texture(Volume, vec3(p.x+Pitch, p.y, p.z)).x
	       - texture(Volume, vec3(p.x-Pitch, p.y, p.z))).x;
	g.y = (texture(Volume, vec3(p.x, p.y+Pitch, p.z)).y
	       - texture(Volume, vec3(p.x, p.y-Pitch, p.z))).y;
	g.z = (texture(Volume, vec3(p.x, p.y, p.z+Pitch)).z
	       - texture(Volume, vec3(p.x, p.y, p.z-Pitch))).z;
	
	// Finish
	g *= 0.5;
	Normal = normalize(-g);
}


/**
 * Computes the ambient and diffuse light for the sample.
 * 
 * @param sample Sampled color at the point.
 */
void shade(inout vec4 sample) {
	
	float nDotL;
	
	// Set up light
	nDotL = max(0.0, dot(Normal, normalize(LightDirection)));
	sample = (sample * Ambient) + (sample * Diffuse * nDotL);
	sample.a = 1.0;
}


void main() {
	
	float t, tExit;
	Ray ray;
	vec4 exit, pos, sample, times;
	
	// Initialize
	exit = texelFetch(Target, ivec2(gl_FragCoord.xy), 0);
	ray.o = TexCoord;
	ray.d = normalize(exit - TexCoord);
	times = (exit - ray.o) / ray.d;
	tExit = min(times.x, min(times.y, times.z));
	Pitch = 1.0 / textureSize(Volume,0).x;
	
	// Sample until out of volume
	FragColor = BLACK;
	while (t < tExit) {
		pos = ray.o + (ray.d * t);
		sample = texture(Volume, pos.stp);
		sample.a = sample.x;
		if (sample.a > 0.3) {
			
			// Shade and composite
			findNormal(pos);
			shade(sample);
			FragColor = mix(FragColor, sample, sample.a);
			if (FragColor.a > 0.9)
				break;
		}
		t += 0.01;
	}
}


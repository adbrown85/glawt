/*
 * Volume.glsl
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Ray.glsl"

/* Uniforms */
uniform float SampleRate=0.02;

/* Outputs */
out vec4 FragColor;


/** Take a sample from the volume and mix it into the output color. */
void Volume_sample(sampler3D volume, Ray ray, float t) {
	
	vec4 value;
	
	value.a = texture(volume, ray.o+(ray.d*t)).x;
	value.rgb = vec3(value.a);
	if (value.a > 0.1) {
		FragColor = mix(FragColor, value, value.a);
	}
}


/** Render a volume.
 * 
 * @param volume 3D texture to sample from.
 * @param ray Ray through the volume.
 * @param start Percentage of the distance to start sampling.
 * @param stop Percentage of the distance to stop sampling.
 */
void Volume_render(sampler3D volume, Ray ray,
                   float start, float stop) {
	
	float t, tStop;
	
	// Initialize direction and times
	tStop = ray.tMax * stop;
	
	// Sample until out of volume
	t = ray.tMax * start;
	while (t < tStop) {
		Volume_sample(volume, ray, t);
		t += SampleRate;
	}
}


/** Render two volumes, alternating between both. */
void Volume_render_two(sampler3D volumeA, Ray rayA,
                       sampler3D volumeB, Ray rayB,
                       float startA, float stopA,
                       float startB, float stopB) {
	
	
	float tA, tB;
	float tStopA, tStopB;
	
	// Initialize direction and times
	tStopA = rayA.tMax * stopA;
	tStopB = rayB.tMax * stopB;
	
	// Sample until out of volume
	tA = rayA.tMax * startA;
	tB = rayB.tMax * startB;
	while (tA < tStopA) {
		Volume_sample(volumeA, rayA, tA);
		Volume_sample(volumeB, rayB, tB);
		tA += SampleRate;
		tB += SampleRate;
	}
}


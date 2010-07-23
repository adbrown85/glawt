/*
 * Volume.glsl
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Ray.glsl"

/* Uniforms */
uniform float SampleRate=0.02;
uniform vec3[5] Colors=vec3[5](BLUE,GREEN,YELLOW,ORANGE,RED);
uniform float[5] Transfer=float[5](0.2, 0.3, 0.4, 0.6, 0.8);

/* Outputs */
out vec4 FragColor;


vec3 Volume_transfer(float value) {
	
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


/** Take a sample from the volume and mix it into the output color. */
void Volume_sample(sampler3D volume, Ray ray, float t) {
	
	vec4 value;
	
	value.a = texture(volume, ray.o+(ray.d*t)).x;
	value.rgb = Volume_transfer(value.a);
	//if (value.a > 0.1) {
		FragColor = mix(FragColor, value, value.a);
	//}
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
void Volume_render_two(sampler3D volumeA, Ray rayA, float startA, float stopA,
                       sampler3D volumeB, Ray rayB, float startB, float stopB) {
	
	float tA, tStopA;
	float tB, tStopB;
	
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


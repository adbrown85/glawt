/*
 * raycaster-lit.frag
 *     Casts rays through a volume with shading.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
uniform int samples, size;
uniform float pitch;
uniform sampler3D volume;
varying vec4 ecPosition, ecRayIncrement, lcRayIncrement;



/**
 * Computes the normal vector for a sample.
 * 
 * @param normal
 *     Normal vector.
 * @param lcPosition
 *     Position in local coordinates.
 * @param pitch
 *     Distance between 
 */
void findNormal(out vec3 normal,
                in vec4 lcPosition) {
	
	float x, y, z;
	vec3 gradient;
	
	/* Make shortcuts for position */
	x = lcPosition.x;
	y = lcPosition.y;
	z = lcPosition.z;
	
	/* Find gradient */
	gradient.x = (texture3D(volume, vec3(x+pitch, y, z))
	             - texture3D(volume, vec3(x-pitch, y, z))).x;
	gradient.y = (texture3D(volume, vec3(x, y+pitch, z))
	             - texture3D(volume, vec3(x, y-pitch, z))).y;
	gradient.z = (texture3D(volume, vec3(x, y, z+pitch))
	             - texture3D(volume, vec3(x, y, z-pitch))).z;
	gradient *= 0.5;
	
	/* Normalize */
	normal = normalize(gl_NormalMatrix * -gradient);
}



/**
 * Computes the diffuse light for the sample.
 */
void shade(inout vec4 sample,
           in vec3 normal) {
	
	float nDotL;
	vec3 L, lightPosition;
	vec4 ambient, diffuse;
	
	/* Set up light */
	lightPosition = vec3(15.0, 15.0, 5.0);
	L = normalize(lightPosition);
	
	/* Compute ambient and diffuse light */
	ambient = vec4(0.8, 0.8, 0.8, 1.0);
	nDotL = max(0.0, dot(normal, L));
	diffuse = vec4(nDotL, nDotL, nDotL, 1.0);
	
	/* Mix in with sample */
	sample.rgb = (sample.rgb * ambient) + (sample.rgb * diffuse);
}



/**
 * Accumulate samples through the volume.
 */
void main() {
	
	float distance;
	vec3 normal;
	vec4 ecRayPosition, lcRayPosition, sample;
	
	/* Form ray */
	lcRayPosition = gl_TexCoord[0];
	ecRayPosition = ecPosition;
	
	/* For each sample */
	for (int i=0; i<samples; ++i) {
		
		/* Move to next position */
		lcRayPosition += lcRayIncrement;
		ecRayPosition += ecRayIncrement;
		
		/* Take sample */
		sample = texture3D(volume, lcRayPosition.stp);
		sample.a = sample.x;
		if (sample.a < 0.01)
			continue;
		
		/* Shade using attenuation */
		distance = length(ecRayPosition);
		sample.rgb /= distance;
		findNormal(normal, lcRayPosition);
		shade(sample, normal);
		
		/* Composite, check for opacity */
		gl_FragColor = mix(gl_FragColor, sample, sample.a);
		if (gl_FragColor.a > 0.9)
			break;
	}
}

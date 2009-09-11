/*
 * raycaster-lit.frag
 *     Casts rays through a volume with shading.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
uniform int samples, size;
uniform sampler3D volume;



/**
 * Composites a sample into the fragment color.
 * 
 * @param sample
 *     New color that will be mixed in.
 * @return
 *     True if the base color has not been completely saturated.
 */
void composite(in vec4 sample) {
	
	/* Mix in colors */
	gl_FragColor = mix(gl_FragColor, sample, sample.a);
}



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
                in vec4 lcPosition,
                in float pitch) {
	
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
 * Calculates the ray direction for this fragment.
 */
vec4 findRayDirection() {
	
	float f=50, n=0.1;
	vec4 cFrag, pFrag;
	vec4 lBack, pBack;
	
	/* Transform fragment to clip space */
	pFrag = gl_ModelViewProjectionMatrix * gl_TexCoord[0];
	cFrag = pFrag / pFrag.w;
	
	/* Find point behind fragment in clip space */
	pBack.w = f;
	pBack.x = cFrag.x * pBack.w;
	pBack.y = cFrag.y * pBack.w;
	pBack.z = f * (f+n)/(f-n) - (2*f*n)/(f-n);
	
	/* Find direction as difference in local space */
	lBack = gl_ModelViewProjectionMatrixInverse * pBack;
	return normalize(lBack - gl_TexCoord[0]);
}



/**
 * Computes the diffuse light for the sample.
 */
void shade(inout vec4 sample,
           in vec4 lcPosition,
           in vec3 normal) {
	
	float nDotL;
	vec4 ecPosition, L, lightPosition;
	
	/* Set up light */
	lightPosition = vec4(15.0, 15.0, 5.0, 1.0);
	
	/* Compute vector from surface to light position */
	ecPosition = gl_ModelViewMatrix * lcPosition;
	L = lightPosition - ecPosition;
	L = normalize(L);
	
	/* Compute dot product between normal and L */
	nDotL = max(0.0, dot(vec4(normal, 1.0), L));
	
	/* Compute intensity */
	sample *= nDotL;
}



/**
 * Samples from the volume.
 * 
 * @param position
 *     Position in the volume.
 * @param sample
 *     Color or value returned.
 * @return
 *     False if the position is outside of the volume.
 */
void takeSample(in vec4 position,
                out vec4 sample) {
	
	/* Get the sample */
	sample = texture3D(volume, position.stp);
	sample.a = sample.x;
}



/**
 * Accumulate samples through the volume.
 */
void main() {
	
	float pitch;
	vec3 normal;
	vec4 rayInc, rayPos, sample;
	
	/* Validate input */
	if (samples == 0)
		samples = 50;
	
	/* Compute constants */
	pitch = 1.0 / size;
	
	/* Form ray */
	rayPos = gl_TexCoord[0];
	rayInc = findRayDirection() * (1.732 / samples);
	
	/* Accumulate color through volume */
	for (int i=0; i<samples; ++i) {
		takeSample(rayPos, sample);
		findNormal(normal, rayPos, pitch);
		shade(sample, rayPos, normal);
		composite(sample);
		rayPos += rayInc;
	}
}

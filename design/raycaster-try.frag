/*
 * raycaster-try.frag
 *     Casts rays through a volume trying different method.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
uniform int samples;
uniform sampler3D volume;



/**
 * Composites a sample into the fragment color.
 * 
 * @param sample
 *     New color that will be mixed in.
 * @return
 *     True if the fragment color is not completely saturated.
 */
bool composite(in vec4 sample) {
	
	/* Mix in colors */
	gl_FragColor = mix(gl_FragColor, sample, sample.a);
	
	/* Check that the color is not completely saturated */
	return true;
/*
	return !((base.x > 0.95) && (base.y > 0.95) && (base.z > 0.95));
*/
}



/**
 * Calculates the ray direction for this fragment.
 */
vec4 findRayDirection() {
	
	float zFar=-50, zNear=-1;
	float f, n;
	vec4 cFrag, pFrag;
	vec4 lBack, pBack;
	
	/* Transform fragment to clip space */
	pFrag = gl_ModelViewProjectionMatrix * gl_TexCoord[0];
	cFrag = pFrag / pFrag.w;
	
	/* Find point behind fragment in clip space */
	f = -(zFar);
	n = -(zNear);
	pBack.w = f;
	pBack.x = cFrag.x * pBack.w;
	pBack.y = cFrag.y * pBack.w;
	pBack.z = f * (f+n)/(f-n) - (2*f*n)/(f-n);
	
	/* Find direction as difference in local space */
	lBack = gl_ModelViewProjectionMatrixInverse * pBack;
	return normalize(lBack - gl_TexCoord[0]);
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
bool takeSample(in vec4 position,
                out vec4 sample) {
	
	/* Test for out of bounds */
/*
	if (position.x < 0.0 || position.x > 1.0)
		return false;
	if (position.y < 0.0 || position.y > 1.0)
		return false;
	if (position.z < 0.0 || position.z > 1.0)
		return false;
*/
	
	/* Get the sample */
	sample = texture3D(volume, position.stp);
	sample.a = sample.x;
	return true;
}



/**
 * Accumulate samples through the volume.
 */
void main() {
	
	float weight;
	vec4 rayInc, rayPos, sample, indicator;
	
	/* Validate input */
	if (samples == 0)
		samples = 50;
	
	/* Form ray */
	rayPos = gl_TexCoord[0];
	rayInc = findRayDirection() * (1.732 / samples);
	
	/* Accumulate color through volume */
	for (int i=0; i<samples; ++i) {
		if (!takeSample(rayPos, sample))
			break;
		if (!composite(sample))
			break;
		rayPos += rayInc;
	}
}

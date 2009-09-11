/*
 * raycaster.frag
 *     Casts rays through a volume.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
uniform float brightness;
uniform int samples;
uniform sampler3D volume;



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
 * Accumulate samples through the volume.
 */
void main() {
	
	float weight;
	vec4 rayDir, rayInc, rayPos, sample;
	
	/* Initialize */
	if (samples == 0)
		samples  = 50;
	weight = 1.0 / samples;
	rayPos = gl_TexCoord[0];
	rayDir = findRayDirection();
	rayInc = rayDir * (1.732 / samples);
	
	/* Accumulate color through volume */
	for (int i=0; i<samples; ++i) {
		sample = texture3D(volume, rayPos.stp) * weight;
		gl_FragColor += sample;
		rayPos += rayInc;
	}
	
	/* Apply brightness */
	if (brightness != 0)
		gl_FragColor *= brightness;
}

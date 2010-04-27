/*
 * raycaster-lit.frag
 *     Casts rays through a volume with shading.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
uniform int samples;
uniform float pitch;
uniform sampler3D volume;



/**
 * Calculates the ray direction.
 * 
 * @return
 *     Ray direction.
 */
vec4 findRayDirection() {
	
	vec4 cFrag, pFrag;
	vec4 lFar, pFar;
	
	/* Transform fragment to clip space */
	pFrag = gl_ModelViewProjectionMatrix * gl_TexCoord[0];
	cFrag = pFrag / pFrag.w;
	
	/* Find point behind fragment in clip space */
	pFar.w = 50;
	pFar.x = cFrag.x * pFar.w;
	pFar.y = cFrag.y * pFar.w;
	pFar.z = 50;
	
	/* Find direction as difference in local space */
	lFar = gl_ModelViewProjectionMatrixInverse * pFar;
	return normalize(lFar - gl_TexCoord[0]);
}




/**
 * Computes the normal vector for a sample.
 * 
 * @param normal
 *     Normal vector.
 * @param P
 *     Position in local coordinates.
 */
void findNormal(out vec3 normal,
                in vec4 P) {
	
	vec3 gradient;
	
	/* Find gradient by central difference */
	gradient.x = (texture3D(volume, vec3(P.x+pitch, P.y, P.z))
	             - texture3D(volume, vec3(P.x-pitch, P.y, P.z))).x;
	gradient.y = (texture3D(volume, vec3(P.x, P.y+pitch, P.z))
	             - texture3D(volume, vec3(P.x, P.y-pitch, P.z))).y;
	gradient.z = (texture3D(volume, vec3(P.x, P.y, P.z+pitch))
	             - texture3D(volume, vec3(P.x, P.y, P.z-pitch))).z;
	gradient *= 0.5;
	
	/* Normalize */
	normal = gl_NormalMatrix * -gradient;
}



/**
 * Computes the ambient and diffuse light for the sample.
 * 
 * @param sample
 *     Sampled color at the point.
 * @param normal
 *     Normal of the point.
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
	
	vec3 normal;
	vec4 rayInc, rayPos, sample;
	
	/* Move along ray */
	rayPos = gl_TexCoord[0];
	rayInc = findRayDirection() * (1.732 / samples);
	for (int i=0; i<samples; ++i) {
		
		/* Take sample */
		rayPos += rayInc;
		sample = texture3D(volume, rayPos.stp);
		sample.a = sample.x;
		if (sample.a > 0.01) {
			
			/* Shade and composite */
			findNormal(normal, rayPos);
			if (normal.x > 0.0 || normal.y > 0.0 || normal.z > 0.0) {
				normal = normalize(normal);
				shade(sample, normal);
				gl_FragColor = mix(gl_FragColor, sample, sample.a);
				if (gl_FragColor.a > 0.9)
					break;
			}
		}
	}
}


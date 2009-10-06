/*
 * raydirection.vert
 *     Finds the ray direction.
 * 
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
uniform int samples;
varying vec4 ecPosition, ecRayIncrement, lcRayIncrement;



/**
 * Calculates the ray direction for this fragment.
 * 
 * @param pcVert
 *     Vertex position in projection coordinates
 */
void computeRayDirection() {
	
	float f=50, n=0.1;
	vec4 ccVert;
	vec4 ecTail, lcTail, pcTail;
	
	/* Find point behind vertex in clip space */
	ccVert = gl_Position / gl_Position.w;
	pcTail.w = f;
	pcTail.x = ccVert.x * pcTail.w;
	pcTail.y = ccVert.y * pcTail.w;
	pcTail.z = f * (f+n)/(f-n) - (2*f*n)/(f-n);
	
	/* Find direction in local and eye coordinates */
	lcTail = gl_ModelViewProjectionMatrixInverse * pcTail;
	ecTail = gl_ProjectionMatrixInverse * pcTail;
	
	/* Find ray increment in local and eye coordinates */
	lcRayIncrement = normalize(lcTail - gl_Vertex) * (1.732 / samples);
	ecRayIncrement = normalize(ecTail - ecPosition) * (1.732 / samples);
}



/**
 * Entry point for the shader.
 * 
 * Needs to compute the "sample direction" in both eye and local coordinates, 
 * as well as the eye position.
 */
void main() {
	
	/* Position in texture, eye, and projection coordinates */
	gl_TexCoord[0] = gl_MultiTexCoord0;
	ecPosition = gl_ModelViewMatrix * gl_Vertex;
	gl_Position = ftransform();
	
	/* Ray direction */
	computeRayDirection();
}


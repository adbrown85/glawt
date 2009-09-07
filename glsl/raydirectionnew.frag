/*
 * raydirectionnew.frag
 *     Visualizes ray direction.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
varying vec4 lFrag;



void main() {
	
	float zFar=-1000, zNear=-0.1;
	float f, n;
	vec4 direction;
	vec4 cFrag, pFrag;
	vec4 lBack, eBack, pBack;
	
	/* Define colors */
	vec4 red=vec4(1.0, 0.0, 0.0, 1.0),
	     green=vec4(0.0, 1.0, 0.0, 1.0),
	     blue=vec4(0.0, 0.0, 1.0, 1.0),
	     yellow=vec4(1.0, 1.0, 0.0, 1.0);
	
	/* Transform fragment to clip space */
	pFrag = gl_ModelViewProjectionMatrix * lFrag;
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
	direction = normalize(lBack - lFrag);
	
	/* Visualize direction */
	if (direction.x < 0)
		gl_FragColor = red;
	else
		gl_FragColor = green;
}

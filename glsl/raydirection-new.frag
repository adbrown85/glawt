/*
 * raydirectionnew.frag
 *     Visualizes ray direction.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */



void main() {
	
	float zFar=-50.0, zNear=-1.0;
	float f, n;
	vec4 direction;
	vec4 cFrag, eFrag, lFrag, pFrag;
	vec4 cBack, eBack, lBack, pBack;
	
	/* Transform fragment to clip space */
	lFrag = gl_TexCoord[0];
	eFrag = gl_ModelViewMatrix * lFrag;
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
	gl_FragColor.rg = (direction.xy + 1) * 0.5;
	gl_FragColor.b = direction.z;
	gl_FragColor.a = 1.0;
}


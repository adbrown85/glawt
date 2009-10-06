/*
 * normal.vert
 *     Provides normal and eye coordinates for fragment shader.
 * 
 * Author
 *     Andy Brown <adb1413@rit.edu> 
 */
varying vec3 normal;
varying vec4 ecPosition;



void main() {
	
	/* Calculate normal */
	normal = normalize(gl_NormalMatrix * gl_Normal);
	
	/* Pass through texture coordinate */
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	/* Convert vertex to eye and projection space */
	ecPosition = gl_ModelViewMatrix * gl_Vertex;
	gl_Position = ftransform();
}


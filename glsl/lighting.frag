/*
 * lighting.frag
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
uniform float ambient;
varying vec3 normal;



/**
 * Computes the ambient light for this fragment.
 */
vec4 ambientLight() {
	
	return vec4(ambient, ambient, ambient, 1.0);
}



/**
 * Computes the diffuse light for this fragment.
 */
vec4 diffuseLight() {
	
	float nDotL;
	vec3 L, lightColor, lightPosition;
	
	/* Set up light */
	lightColor = vec3(0.0, 0.0, 1.0);
	lightPosition = vec3(15.0, 15.0, 5.0);
	
	/* Compute intensity that reaches point */
	L = normalize(lightPosition);
	nDotL = max(0.0, dot(normal, L));
	return vec4(lightColor * nDotL, 1.0);
}



/**
 * Computes the color of the fragment from ambient and diffuse light.
 */
void main() {
	
	/* Color from ambient and diffuse light */
	gl_FragColor = ambientLight() + diffuseLight();
}

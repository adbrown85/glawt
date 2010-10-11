/*
 * Shadow.vert
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

/* Uniforms */
uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix;
uniform vec3 LightPosition;
uniform float Ambient;
uniform mat4 MCtoLightMatrix;

/* Inputs */
in vec4 MCVertex;
in vec3 MCNormal;

/* Outputs */
out float LightIntensity;
out vec3 ShadowCoord;


/** Compute vertex position. */
void main() {
	
	// Initialize
	vec3 ecPosition = vec3(MVMatrix * MCVertex);
	vec3 tnorm = normalize(NormalMatrix * MCNormal);
	vec3 lightVec = normalize(LightPosition - ecPosition);
	vec3 viewVec = normalize(-ecPosition);
	
	// Computations
	LightIntensity = Ambient + max(dot(lightVec, tnorm), 0.0);
	ShadowCoord = (MCtoLightMatrix * MCVertex).xyz;
	gl_Position = MVPMatrix * MCVertex;
}


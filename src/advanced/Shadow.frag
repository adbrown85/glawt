/*
 * Shadow.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

/* Uniforms */
uniform vec4 Color=vec4(1,1,1,1);
uniform sampler2DShadow ShadowMap;

/* Inputs */
in float LightIntensity;
in vec4 ShadowCoord;

/* Outputs */
out vec4 FragColor;


/** Compute fragment color. */
void main() {
	
	float shadeFactor;
	
	shadeFactor = textureProj(ShadowMap, ShadowCoord) * 0.25 + 0.75;
	FragColor = Color * LightIntensity * shadeFactor;
/*
	FragColor = Color * LightIntensity;
*/
}


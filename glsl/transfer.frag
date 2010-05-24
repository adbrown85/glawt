/*
 * transfer.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

/* Uniforms */
uniform float Pivot=0.5;
uniform vec3[3] Colors=vec3[3](vec3(1,0,1),vec3(0,1,1),vec3(1,1,0));

/* Inputs */
in vec3 Coord;

/* Outputs */
out vec4 FragColor;


/** Computes the fragment color. */
void main() {
	
	float value;
	float[3] markers=float[3](0.0, Pivot, 1.0);
	
	value = Coord.s;
	for (int i=1; i<3; ++i) {
		if (value < markers[i]) {
			value = smoothstep(markers[i-1], markers[i], value);
			FragColor = vec4(mix(Colors[i-1],Colors[i],value), 1.0);
			break;
		}
	}
}


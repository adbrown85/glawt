/*
 * target-alpha.frag
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#version 130
#include "Colors.glsl"

/* Uniforms */
uniform sampler2D Target;
uniform int CanvasSize=512;

/* Outputs */
out vec4 FragColor;


/** Sets color to alpha value in the target at this pixel. */
void main() {
	
	float alpha;
	
	alpha = texture(Target, gl_FragCoord.xy/CanvasSize).a;
	if (alpha < 0.98) {
		FragColor = GREEN;
	} else if (alpha < 0.99) {
		FragColor = RED;
	} else {
		FragColor = BLUE;
	}
	FragColor.a = 1.0;
}


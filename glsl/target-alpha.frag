/*
 * target-alpha.frag
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#version 130
#include "Colors.glsl"
#include "Target.glsl"

/* Uniforms */
uniform sampler2D Target;

/* Outputs */
out vec4 FragColor;


/** Sets color to alpha value in the target at this pixel. */
void main() {
	
	float alpha;
	
	alpha = Target_getValue(Target).a;
	FragColor.rgb = vec3(alpha);
	FragColor.a = 1.0;
}


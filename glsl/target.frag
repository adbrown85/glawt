/*
 * target.frag
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#version 130

/* Uniforms */
uniform sampler2D Target;
uniform int Size=512;

/* Outputs */
out vec4 FragColor;


/** Sets the color to the value of the same position in the target. */
void main() {
	
	FragColor = texture(Target, gl_FragCoord.xy/Size);
	if (FragColor.a == 0) {
		discard;
	}
}


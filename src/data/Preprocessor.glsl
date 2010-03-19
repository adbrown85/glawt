/*
 * Preprocessor.glsl
 *     Tests Preprocessor class.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#define COOL_MACRO
#include "../../input/Ray.glsl"
#include "../../input/Ray.glsl"
#define SOME_CONSTANT 3.14



void main() {
	
	float value;
	
	// A comment!
	value = 1 / 8;
	value = 1 * SOME_CONSTANT;
	gl_FragColor = gl_TexCoord[0];		// Another comment
	/* This one might be tricky! */
}


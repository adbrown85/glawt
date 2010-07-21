/*
 * Target.glsl
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */

/* Uniforms */
uniform int CanvasSize=512;


/** Retrieve a stored value from a render target. */
vec4 Target_getValue(sampler2D target) {
	
	return texture(target, gl_FragCoord.xy/CanvasSize);
}


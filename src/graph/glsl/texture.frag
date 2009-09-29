/*
 * texture.frag
 *     Applies a texture.
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
uniform sampler2D tex;


void main() {
	
	gl_FragColor = texture2D(tex, gl_TexCoord[0].st);
}


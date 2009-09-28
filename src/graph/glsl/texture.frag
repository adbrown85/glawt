/*
 * texture.frag
 *     Applies a texture.
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
uniform sampler2D texture;


void main() {
	
	gl_FragColor = texture2D(texture, gl_TexCoord[0].st);
}


/*
 * texture.frag
 *     Allows the user to select a texture with a uniform.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
uniform sampler2D texture;



void main() {
	
	gl_FragColor = texture2D(texture, gl_TexCoord[0].st);
}


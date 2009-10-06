/*
 * multitexture.frag
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
uniform sampler2D left, right;


void main() {
	
	if (gl_TexCoord[0].s < 0.5)
		gl_FragColor = texture2D(left, gl_TexCoord[0].st);
	else
		gl_FragColor = texture2D(right, gl_TexCoord[0].st);
}


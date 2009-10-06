/*
 * coordinates.frag
 *     Sets the fragment equal to its coordinates.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */



void main() {
	
	gl_FragColor = gl_TexCoord[0];
}


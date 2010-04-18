/*
 * coordinates.frag
 *     Sets the fragment equal to its coordinates.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#version 110


void main() {
	
	gl_FragColor = gl_TexCoord[0];
}


/*
 * window.frag
 * 
 * Author
 *     Andrew Brown
 */


void main() {
	
	gl_FragColor.rg = gl_FragCoord.xy / 512;
	gl_FragColor.a = 1.0;
}


/*
 * Octree.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
uniform sampler1D octree;


void main() {
	
	if (gl_TexCoord[0].s < 0.01
	      || gl_TexCoord[0].s > 0.99
	      || gl_TexCoord[0].t < 0.01
	      || gl_TexCoord[0].t > 0.99) {
		gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
	} else {
		gl_FragColor = texture1D(octree, gl_TexCoord[0].s);
	}
}


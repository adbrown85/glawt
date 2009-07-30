/*
 * raycaster.frag
 *     Casts rays through a volume.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
uniform int samples;
uniform float brightness;
uniform sampler3D volume;
varying vec4 vertexPosition;
vec4 red=vec4(1.0, 0.0, 0.0, 1.0),
     green=vec4(0.0, 1.0, 0.0, 1.0),
     blue=vec4(0.0, 0.0, 1.0, 1.0);



/**
 * Samples the volume and colorizes it.
 * 
 * @param texPosition
 *     Position in texture coordinates.
 */
vec4 sample(in vec4 texPosition) {
	
	vec4 voxel;
	
	/* Colorize voxel */
	voxel = texture3D(volume, texPosition.stp);
	return voxel * green * brightness;
}



/**
 * Converts a position in global coordinates to texture coordinates.
 * 
 * @param gloPos
 *     Position in global coordinates.
 * @param texPos
 *     Position in texture coordinates.
 * @return
 *     False if the texture coordinates are out of bounds.
 */
bool transform(in vec4 gloPos,
               inout vec4 texPos) {
	
	/* Convert to local position */
	texPos = gl_ModelViewMatrixInverse * gloPos;
	
	/* Catch out-of-bounds coordinates */
	if (texPos.x < -0.002 || texPos.x > 1.002)
		return false;
	if (texPos.y < -0.002 || texPos.y > 1.002)
		return false;
	if (texPos.z < -0.002 || texPos.z > 1.002)
		return false;
	
	/* Good coordinate */
	return true;
}



/**
 * Calculates a ray from the fragment's position and accumulate samples 
 * through the volume.
 */
void main() {
	
	float weight=1.0/samples;
	vec4 rayColor, rayDirection, rayPosition, texPosition;
	
	/* Calculate ray */
	rayPosition = vertexPosition;
	rayDirection = vertexPosition;
	rayDirection = normalize(rayDirection);
	rayDirection = vec4(0.0, 0.0, -1.0, 0.0);
	
	/* For each sample */
	for (int i=0; i<samples; ++i) {
		
		/* Accumulate color */
		if (transform(rayPosition, texPosition))
			rayColor += sample(texPosition) * weight;
		else
			break;
		
		/* Update ray position */
		rayPosition += rayDirection * weight;
	}
	
	/* Set final color */
	gl_FragColor = rayColor;
}

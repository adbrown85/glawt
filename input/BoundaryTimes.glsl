/*
 * BoundaryTimes.glsl
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BOUNDARYTIMES_GLSL
#define BOUNDARYTIMES_GLSL


/**
 * Holds times that a ray strikes a bounding box.
 */
struct BoundaryTimes {
	vec3 t0, t1, th;
};


#endif

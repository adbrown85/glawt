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


/**
 * Default constructor.
 */
BoundaryTimes BoundaryTimes_() {
	
	BoundaryTimes times;
	
	times.t0 = vec3(0,0,0);
	times.t1 = vec3(0,0,0);
	times.th = vec3(0,0,0);
	return times;
}


/**
 * Finds where the ray actually intersects a bounding box.
 * 
 * @param times Instance
 * @param tEnter Time where the ray enters the bounding box
 * @param tLeave Time where the ray leaves the bounding box
 */
void BoundaryTimes_getIntersections(in BoundaryTimes times,
                                    out float tEnter,
                                    out float tLeave) {
	
	vec3 tMin, tMax;
	
	// Find min and max
	for (int i=0; i<3; ++i) {
		tMin[i] = min(times.t0[i], times.t1[i]);
		tMax[i] = max(times.t0[i], times.t1[i]);
	}
	
	// Get times where it enters and exits
	tEnter = max(tMin.x, max(tMin.y,tMin.z));
	tLeave = min(tMax.x, min(tMax.y,tMax.z));
}


#endif

/*
 * BoundingBox.glsl
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BOUNDINGBOX_GLSL
#define BOUNDINGBOX_GLSL
#include "BoundaryTimes.glsl"
#include "Ray.glsl"


/**
 * Bounding box.
 */
struct BoundingBox {
	vec4 center, lower, upper;
};


/**
 * Constructs a default BoundingBox.
 * 
 * @returns default BoundingBox instance.
 */
BoundingBox BoundingBox_() {
	
	BoundingBox box;
	
	box.lower = vec4(0,0,0,1);
	box.upper = vec4(1,1,1,1);
	box.center = vec4(0.5,0.5,0.5,1);
	return box;
}


/**
 * Calculates when a ray hits the bounding box.
 * 
 * @param [in] box BoundingBox instance.
 * @param [in] ray Ray instance.
 */
BoundaryTimes BoundingBox_calculateTimes(in BoundingBox box,
                                         in Ray ray) {
	
	BoundaryTimes times;
	
	// Lower boundary
	times.t0.x = (box.lower.x - ray.o.x) / ray.d.x;
	times.t0.y = (box.lower.y - ray.o.y) / ray.d.y;
	times.t0.z = (box.lower.z - ray.o.z) / ray.d.z;
/*
	times.t0.x = Ray_getTimeAt(ray, 0, box.lower.x);
	times.t0.y = Ray_getTimeAt(ray, 1, box.lower.y);
	times.t0.z = Ray_getTimeAt(ray, 2, box.lower.z);
*/
	
	// Upper boundary
	times.t1.x = (box.upper.x - ray.o.x) / ray.d.x;
	times.t1.y = (box.upper.y - ray.o.y) / ray.d.y;
	times.t1.z = (box.upper.z - ray.o.z) / ray.d.z;
/*
	times.t1.x = Ray_getTimeAt(ray, 0, box.upper.x);
	times.t1.y = Ray_getTimeAt(ray, 1, box.upper.y);
	times.t1.z = Ray_getTimeAt(ray, 2, box.upper.z);
*/
	
	// Center
	times.th.x = (box.center.x - ray.o.x) / ray.d.x;
	times.th.y = (box.center.y - ray.o.y) / ray.d.y;
	times.th.z = (box.center.z - ray.o.z) / ray.d.z;
/*
	times.th.x = Ray_getTimeAt(ray, 0, box.center.x);
	times.th.y = Ray_getTimeAt(ray, 1, box.center.y);
	times.th.z = Ray_getTimeAt(ray, 2, box.center.z);
*/
	
	// Finish
	return times;
}


#endif

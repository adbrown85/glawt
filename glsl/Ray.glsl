/*
 * Ray.glsl
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef RAY_GLSL
#define RAY_GLSL


/** Ray with origin and direction. */
struct Ray {
	vec3 o;
	vec3 d;
	float tMax;
};


/** Ray constructor.
 * 
 * @param [in,out] ray Ray instance.
 * @param [in] origin Origin of the ray.
 * @param [in] end End of the ray.
 */
void Ray_(inout Ray ray,
          in vec3 origin,
          in vec3 end) {
	
	ray.o = origin;
	ray.d = normalize(end - origin);
}


Ray Ray_construct(in vec3 origin, in vec3 exit) {
	
	Ray ray;
	vec3 span, times;
	
	// Span
	span = exit - origin;
	
	// Origin and direction
	ray.o = origin;
	ray.d = normalize(span);
	
	// tMax
	times = (span) / ray.d;
	ray.tMax = min(times.x, min(times.y, times.z));
	
	// Finish
	return ray;
}


/** Determines if part of the direction is parallel to an axis.
 * 
 * @param [in] component x=0, y=1, z=2
 */
/*
bool Ray_isDirectionZero(int component) {
	
	return true;
}
*/


/** @return point along the ray at the time.
 * 
 * @param [in] ray Ray instance.
 * @param [in] t Time at the point.
 */
/*
vec4 Ray_getPointAt(in Ray ray,
                    in float t) {
	
	return vec4(0,0,0,1);
}
*/


/** @return time along the ray at a value along one axis.
 * 
 * @param [in] ray Ray instance.
 * @param [in] i Axis where x=0, y=1, z=2
 * @param [in] value Value on that axis.
 */
float Ray_getTimeAt(in Ray ray,
                    in int i,
                    in float value) {
	
	// If parallel to axis use infinity based on origin
	if (abs(ray.d[i]) < 0.0000001) {
		if (value < ray.o[i]) {
			return -1024.0;
		} else if (value > ray.o[i]) {
			return +1024.0;
		} else {
			return 0.0;
		}
	}
	
	// Otherwise just calculate normally
	return (value - ray.o[i]) / ray.d[i];
}


bool Ray_isNegative(in Ray ray) {
	
	return ray.d.x < 0.0 || ray.d.y < 0.0 || ray.d.z < 0.0;
}


/** @return value at a time along one axis.
 * 
 * @param [in] ray Ray instance.
 * @param [in] axis x=0, y=1, z=2
 * @param [in] t Time along the ray.
 */
/*
float Ray_getValueAt(in Ray ray,
                     in int axis,
                     in float t) {
	
	return 1;
}
*/



#endif

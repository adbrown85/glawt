/*
 * Camera.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "common.h"
#include <GL/glu.h>
#include "Matrix.hpp"
#include "Quaternion.hpp"
#include "Vector.hpp"
#include "State.hpp"
#define CAMERA_DEFAULT_ZOOM -10.0
#define CAMERA_ROTATE_AMOUNT 5.0
using namespace std;


/** @brief Encapsulation of rotation and position for a view.
 * @ingroup graphics
 */
class Camera {
public:
	void apply();
	Vector getPosition() const;
	Matrix getRotation() const;
	Matrix getRotationMatrix() const;
	Matrix getTranslationMatrix() const;
	Matrix getViewMatrix() const;
	void load(int width, int height);
	void move(const Vector &amount);
	void reset();
	void rotate(float angle, const Vector &axis);
private:
	Quaternion rotation;
	Vector position;
};

/** @return Position of the camera. */
inline Vector Camera::getPosition() const {return position;}

/** @return Rotation of the camera. */
inline Matrix Camera::getRotation() const {return rotation.getMatrix();}

/** @return Rotation of the camera as a matrix. */
inline Matrix Camera::getRotationMatrix() const {return rotation.getMatrix();}



#endif

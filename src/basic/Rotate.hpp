/*
 * Rotate.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef ROTATE_HPP
#define ROTATE_HPP
#include "common.h"
#include "Transformation.hpp"
#include "Vector.hpp"
#include "Quaternion.hpp"
using namespace std;


/** @brief %Node that reorients items in the scene.
 * @ingroup basic
 */
class Rotate : public Transformation {
public:
	Rotate(const Tag &tag);
	virtual void apply();
	virtual void applyTo(Matrix &matrix);
	virtual void remove();
	virtual string toString() const;
private:
	float angle;
	Vector axis;
	Quaternion quaternion;
};


#endif

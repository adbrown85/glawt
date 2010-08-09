/*
 * Scale.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SCALE_HPP
#define SCALE_HPP
#include "common.h"
#include "Transform.hpp"
#include "Vector.hpp"
using namespace std;


/** @brief %Node that resizes items in the scene.
 * @ingroup basic
 */
class Scale : public Transform,
              public Vector {
public:
	Scale(const Tag &tag);
	virtual void add(const Vector &B);
	virtual void apply();
	virtual void applyTo(Matrix &matrix);
	static Scale* find(Node *node);
	virtual void remove();
	virtual bool setAttribute(pair<string,string> attribute);
	virtual string toString() const;
private:
	float value;
};


#endif

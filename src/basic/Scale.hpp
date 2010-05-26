/*
 * Scale.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SCALE_HPP
#define SCALE_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <GL/glut.h>
#include "Transformation.hpp"
#include "Vector.hpp"
using namespace std;


/**
 * @ingroup basic
 * @brief %Node that resizes items in the scene.
 */
class Scale : public Transformation,
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

/*
 * Manipulator.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MANIPULATOR_HPP
#define MANIPULATOR_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include "Delegate.hpp"
#include "Drawable.hpp"
#include "Identifiable.hpp"
#include "Scene.hpp"
#include "Vector.hpp"


/**
 * @ingroup frontend
 * @brief
 *     Abstract base class for an item that manipulates other items.
 */
class Manipulator : public Identifiable {
public:
	Manipulator();
	void copySizeOf(const Drawable &other);
	virtual void draw() const = 0;
	Vector getAxis() const;
	void setDelegate(Delegate *delegate);
	virtual void use(Scene *scene,
	                 const Vector &movement,
	                 GLuint shapeID) = 0;
protected:
	float size;
	Delegate *delegate;
	Vector axis;
};


inline Manipulator::Manipulator() {
	this->delegate = NULL;
}

/**
 * Makes the manipulator the same size as a drawable object.
 * 
 * @param drawable Reference to a drawable object.
 */
inline void Manipulator::copySizeOf(const Drawable &drawable) {
	this->size = drawable.getSize();
}

inline Vector Manipulator::getAxis() const {
	return axis;
}

inline void Manipulator::setDelegate(Delegate *delegate) {
	this->delegate = delegate;
}


#endif

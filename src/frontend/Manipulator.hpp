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
#include "Interpreter.hpp"              // For sending commands
#include "Drawable.hpp"
#include "Identifiable.hpp"
#include "Scene.hpp"                    // Need to send to commands
#include "Vector.hpp"                   // For axis


/**
 * @ingroup frontend
 * @brief Abstract base class for an item that manipulates other items.
 * 
 * @todo Can probably get rid of copySizeOf().  Wouldn't need "Drawable.hpp".
 */
class Manipulator : public Identifiable {
public:
	Manipulator();
	void copySizeOf(const Drawable &other);
	virtual void draw() const = 0;
	Vector getAxis() const;
	void setInterpreter(Interpreter *interpreter);
	virtual void use(Scene *scene, const Vector &movement, GLuint shapeID) = 0;
protected:
	float size;
	Interpreter *interpreter;
	Vector axis;
};


/** Creates a manipulator that cannot send commands yet. */
inline Manipulator::Manipulator() {this->interpreter = NULL;}

/** @return Direction the manipulator is oriented in. */
inline Vector Manipulator::getAxis() const {return axis;}

/** Changes the object to send commands to. */
inline void Manipulator::setInterpreter(Interpreter *i) {this->interpreter = i;}


/** Makes the manipulator the same size as a drawable object. */
inline void Manipulator::copySizeOf(const Drawable &drawable) {
	this->size = drawable.getSize();
}


#endif

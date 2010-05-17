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
#include "Transform.hpp"                // Projection matrix


/**
 * @ingroup frontend
 * @brief Abstract base class for an item that manipulates other items.
 */
class Manipulator : public Identifiable {
public:
	Manipulator();
	virtual void draw() const = 0;
	float findPixelFactor(GLuint shapeID);
	Vector getAxis() const;
	bool isEnabled() const;
	void setEnabled(bool enabled);
	void setInterpreter(Interpreter *interpreter);
	virtual void use(const Vector &movement, GLuint shapeID) = 0;
protected:
	bool enabled;
	float size;
	Interpreter *interpreter;
	Vector axis;
};

/** @return Direction the manipulator is oriented in. */
inline Vector Manipulator::getAxis() const {return axis;}

inline bool Manipulator::isEnabled() const {return enabled;}

inline void Manipulator::setEnabled(bool enabled) {this->enabled = enabled;}

/** Changes the object to send commands to. */
inline void Manipulator::setInterpreter(Interpreter *i) {this->interpreter = i;}


#endif

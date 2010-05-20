/*
 * Manipulator.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MANIPULATOR_HPP
#define MANIPULATOR_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <GL/glut.h>
#include "Interpreter.hpp"              // For sending commands to scene
#include "Vector.hpp"                   // For axis
#include "Transform.hpp"                // Projection matrix
#include "Traverser.hpp"


/**
 * @ingroup frontend
 * @brief Abstract base class for an item that manipulates other items.
 */
class Manipulator : public Identifiable {
public:
	Manipulator(char axis,
	            int command,
	            string filename,
	            const string &warning="May not be able to use manipulator.");
	virtual ~Manipulator();
	virtual void draw() const;
	static float findPixelFactor(GLuint shapeID);
	virtual Vector getAxis() const;
	virtual int getCommand() const;
	virtual bool isEnabled() const;
	virtual void setEnabled(bool enabled);
	virtual void setInterpreter(Interpreter *interpreter);
	virtual void use(const Vector &movement, GLuint shapeID);
protected:
	bool enabled;
	int command;
	Interpreter *interpreter;
	Scene *widget;
	Traverser *traverser;
	Vector axis;
};

/** @return Direction the manipulator is oriented in. */
inline Vector Manipulator::getAxis() const {return axis;}

/** @return Enumerated command to run when the user drags the manipulator. */
inline int Manipulator::getCommand() const {return command;}

/** @return True if the manipulator should be drawn. */
inline bool Manipulator::isEnabled() const {return enabled;}

/** Determines if the manipulator should be drawn. */
inline void Manipulator::setEnabled(bool enabled) {this->enabled = enabled;}

/** Changes the object to send commands to. */
inline void Manipulator::setInterpreter(Interpreter *i) {this->interpreter = i;}


#endif

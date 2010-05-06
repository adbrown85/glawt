/*
 * Boolean.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BOOLEAN_HPP
#define BOOLEAN_HPP
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <limits>                       // Calculating result
#include <list>                         // Storing shapes
#include <queue>                        // Finding shapes
#include "Group.hpp"
#include "Shape.hpp"
#include "Transformation.hpp"
#include "Transform.hpp"
using namespace std;


/**
 * @ingroup advanced
 * @brief Combines shapes in different ways to create a new one.
 */
class Boolean : public Shape,
                public NodeListener {
public:
	Boolean(const Tag &tag);
	virtual void associate();
	virtual void finalize();
	virtual void draw() const;
	virtual void nodeUpdated();
	virtual string toString() const;
protected:
	void calculate();
	void calculate(Node *node);
	void findGroup();
	void findShapes();
	void findTransforms();
	void initIndices();
	void initPoints();
	void initBuffers();
private:
	bool tangible;
	GLuint dataBuffer, indicesBuffer;
	GLfloat points[8][3];
	GLshort indices[24];
	Group *group;
	list<Shape*> shapes;
	Matrix mvm;
	string of, operation;
	static float FLT_INF;
	Vector upper, lower;
};


#endif

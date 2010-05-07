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
#include "UniformSampler.hpp"
using namespace std;


/** Upper and lower boundaries of a shape. */
struct Extent {
	Vector upper, lower, diagonal;
};

/** Texture coordinates of a shape. */
struct Coordinates {
	Vector upper, lower;
};


/**
 * @ingroup advanced
 * @brief Combines shapes in different ways to create a new one.
 */
class Boolean : public Shape,
                public NodeListener {
public:
	Boolean(const Tag &tag);
	virtual void associate();
	virtual void draw() const;
	virtual void finalize();
	virtual void nodeUpdated();
	virtual string toString() const;
protected:
	void findGroup();
	UniformSampler* findSampler(Shape *shape);
	void findShapes();
	void findTransforms();
	void initBuffers();
	void initIndices();
	void initPoints();
	void update();
	void updateExtents();
	void updateExtents(Node *node);
	void updateCoords();
	void updatePoints();
	void updateTangible();
	void updateUpperLower();
private:
	bool tangible;
	GLuint dataBuffer, indicesBuffer;
	GLfloat points[8][3], coords0[8][3], coords1[8][3];
	GLshort indices[24];
	Group *group;
	//list<Shape*> shapes;
	//map<Shape*,Matrix> inverses;
	map<Shape*,Extent> extents;
	map<int,Coordinates> units;
	Matrix mvm;
	string of, operation;
	static float FLT_INF;
	Vector upper, lower;
};


inline void Boolean::nodeUpdated() {update();}


#endif

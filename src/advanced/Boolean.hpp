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
#include "Hexahedron.hpp"
using namespace std;


/* Upper and lower boundaries of a shape. */
struct Extent {
	Vector upper, lower, diagonal;
	int label;
};

/* Texture coordinates of a shape. */
struct Coordinates {
	Vector upper, lower;
};


/**
 * @ingroup advanced
 * @brief Combines shapes in different ways to create a new one.
 * 
 * To create a concrete operation, subclass %Boolean and implement 
 * isTangible() and updateAttributes().  Of course, make sure to pass the 
 * right number of vertices and all the attribute names in the constructor.
 */
class Boolean : public Hexahedron,
                public NodeListener {
public:
	Boolean(const Tag &tag, ShapeTraits traits);
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
	virtual void initAttributes();
	bool isOverlapped();
	void update();
	void updateExtents();
	void updateExtents(Node *node);
	void updateOverlap();
	virtual void updateTangible() = 0;
protected:
	bool tangible;
	Extent overlap;
	Group *group;
	map<Shape*,Extent> extents;
	map<int,Coordinates> units;
	Matrix mvm;
	string of, operation;
	static float FLT_INF;
};


#endif

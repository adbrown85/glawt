/*
 * Boolean.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BOOLEAN_HPP
#define BOOLEAN_HPP
#include "common.h"
#include <limits>                       // Calculating result
#include <vector>                       // Storing shapes and extents
#include "Group.hpp"
#include "Shape.hpp"
#include "Transformation.hpp"
#include "Transform.hpp"
#include "Hexahedron.hpp"
using namespace std;


/* Upper and lower boundaries of a shape. */
struct Extent {
	Vector upper, lower, diagonal;
	int label;
};


/** @brief Combines shapes in different ways to create a new one.
 * 
 * To create a concrete operation, subclass %Boolean and implement 
 * isTangible() and updateAttributes().  Of course, make sure to pass the 
 * right number of vertices and all the attribute names in the constructor.
 * 
 * @ingroup advanced
 */
class Boolean : public Hexahedron {
public:
	Boolean(const Tag &tag, ShapeTraits traits);
	virtual void associate();
	virtual void draw() const;
	virtual void finalize();
	virtual void onNodeEvent(NodeEvent &event);
	virtual string toString() const;
protected:
	void calculate();
	void calculateExtents();
	void calculateExtents(Node *node);
	void calculateOverlap();
	virtual void calculateTangible() = 0;
	void findGroup();
	virtual void findShapes();
	void findTransforms();
	bool isOverlapped();
	bool isSubstantial(const Extent &extent);
	virtual void updateBuffer();
protected:
	bool tangible;
	Extent overlap;
	Group *group;
	vector<Shape*> shapes;
	vector<Extent> extents;
	Matrix mvm;
	string of, operation;
	static float FLT_INF;
};


#endif

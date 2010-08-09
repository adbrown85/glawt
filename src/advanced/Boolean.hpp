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
#include "Hexahedron.hpp"
#include "Factory.hpp"
#include "Uniform.hpp"
#include "Suppressor.hpp"
#include "State.hpp"
using namespace std;


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
	virtual ~Boolean();
	virtual void associate();
	virtual void draw() const;
	virtual void finalize();
	virtual void onNodeEvent(NodeEvent &event);
	virtual string toString() const;
protected:
	void applyUniforms() const;
	void applyUniforms(int i) const;
	void associateUniforms();
	void calculate();
	void calculateExtents();
	void calculateExtents(Node *node);
	void calculateOverlap();
	virtual void calculateTangible() = 0;
	void finalizeUniforms();
	void findGroup();
	void findShapes();
	void findTransforms();
	void findUniforms();
	bool isOverlapped() const;
	virtual void updateBuffer();
protected:
	static bool isSubstantial(const Extent &extent);
protected:
	bool tangible;
	Extent overlap;
	Group *group;
	vector<Shape*> shapes;
	vector<Extent> extents;
	list<Uniform*> uniforms[2];
	Matrix mvm;
	string of, operation;
	Suppressor suppressor;
protected:
	static float FLT_INF;
};


#endif

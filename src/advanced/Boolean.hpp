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
class Boolean : public Shape {
public:
	Boolean(const Tag &tag);
	virtual void associate();
	virtual void draw() const;
	virtual string toString() const;
protected:
	void calculate(Node *node, Vector &upper, Vector &lower) const;
	void findGroup();
	void findShapes();
private:
	Group *group;
	list<Shape*> shapes;
	string of, operation;
	static float FLT_INF;
};


#endif

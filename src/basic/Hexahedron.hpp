/*
 * Hexahedron.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef HEXAHEDRON_HPP
#define HEXAHEDRON_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include "Shape.hpp"
using namespace std;


/**
 * @ingroup basic
 * @brief Six-sided shape.
 * 
 * %Hexahedron is an abstract base class for a six-sided shape.  It provides 
 * points and normals, but no texture coordinates.
 * 
 * The following diagram depicts which vertices correspond to which points and 
 * faces.
 * <pre>
 *       front            left               top
 *     +-------+        9-------+         17-----16
 *    /|      /|       /|      /|        /|      /|
 *   1-------0 |      8-------+ |       18-----19 |
 *   | +-----|-+      | 10----|-+       | +-----|-+
 *   |/      |/       |/      |/        |/      |/
 *   2-------3        11------+         +-------+
 * 
 *       back             right            bottom
 *     4-------5        +------12        +-------+
 *    /|      /|       /|      /|       /|      /|
 *   +-------+ |      +------13 |      +-------+ |
 *   | 7-----|-6      | +-----|15      | 22----|23
 *   |/      |/       |/      |/       |/      |/
 *   +-------+        +------14        21-----20
 * </pre>
 */
class Hexahedron : public Shape {
public:
	Hexahedron(const Tag &tag);
	static list<string> getAttributes();
	virtual void initAttributeValues();
protected:
	virtual void load();
	virtual void initPoints();
	virtual void initNormals();
	virtual void initCoords() = 0;
protected:
	static bool loaded;
	static int indices[8][3];
};


#endif

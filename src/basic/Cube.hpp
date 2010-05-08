/*
 * Cube.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CUBE_HPP
#define CUBE_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Hexahedron.hpp"
using namespace std;


/**
 * @ingroup basic
 * @brief Six-sided shape with 3D texture coordinates.
 */
class Cube : public Hexahedron {
public:
	Cube(const Tag &tag) : Hexahedron(tag,getTraits()) {};
protected:
	virtual void initCoords();
};


#endif

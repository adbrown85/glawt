/*
 * Translator.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/gl.h>
#include <vector>
#include "Manipulator.hpp"
#include "Matrix.hpp"
#include "Scene.hpp"
#include "Selection.hpp"
#include "Shape.hpp"
#include "Translate.hpp"
#include "Traverser.hpp"
#include "Vector.hpp"
#include "Window.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief Tool for moving shapes.
 */
class Translator : public Manipulator {
public:
	Translator(float x, float y, float z);
	~Translator();
	virtual void draw() const;
	void use(const Vector &movement, GLuint shapeID);
private:
	Scene *geometry;
	Traverser *traverser;
};


#endif

/*
 * BasicFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef BASICFACTORY_HPP
#define BASICFACTORY_HPP
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include "Exception.hpp"
#include "Factory.hpp"
#include "Box.hpp"
#include "Cube.hpp"
#include "Program.hpp"
#include "Scale.hpp"
#include "Shader.hpp"
#include "Square.hpp"
#include "Texture2D.hpp"
#include "Texture3D.hpp"
#include "Translate.hpp"
#include "UniformInt.hpp"
#include "UniformFloat.hpp"
#include "UniformMatrix.hpp"
#include "UniformSampler.hpp"
#include "UniformVector.hpp"
using namespace std;


/**
 * @ingroup basic
 * @brief %Factory for creating nodes used by most files.
 */
class BasicFactory {
public:
	static void install();
	static Node* createBox(const Tag &tag);
	static Node* createCube(const Tag &tag);
	static Node* createProgram(const Tag &tag);
	static Node* createScale(const Tag &tag);
	static Node* createShader(const Tag &tag);
	static Node* createSquare(const Tag &tag);
	static Node* createTexture(const Tag &tag);
	static Node* createTranslate(const Tag &tag);
	static Node* createUniform(const Tag &tag);
private:
	enum kind_t {INT, FLOAT, MATRIX, SAMPLER, VECTOR};
	static bool installed;
	static map<string,kind_t> kinds;
};


#endif

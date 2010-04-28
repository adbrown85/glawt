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
#include "Factory.hpp"
#include "Cube.hpp"
#include "Program.hpp"
#include "Scale.hpp"
#include "Shader.hpp"
#include "Square.hpp"
#include "Texture2D.hpp"
#include "Texture3D.hpp"
#include "Translation.hpp"
#include "UniformInt.hpp"
#include "UniformFloat.hpp"
#include "UniformMatrix.hpp"
#include "UniformSampler.hpp"
#include "UniformVector.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief
 *     Factory for creating nodes used by most files.
 */
class BasicFactory {
	
	
	public:
		
		static void install();
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

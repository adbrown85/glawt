/*
 * ShaderFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SHADERFACTORY_HPP
#define SHADERFACTORY_HPP
#include <cstdlib>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include "Factory.hpp"
#include "Program.hpp"
#include "Shader.hpp"
#include "UniformInt.hpp"
#include "UniformFloat.hpp"
#include "UniformMatrix.hpp"
#include "UniformSampler.hpp"
#include "UniformVector.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief
 *     Factory for creating nodes related to shaders.
 */
class ShaderFactory : public Factory {
	
	public:
		
		ShaderFactory();
		virtual Node* create(const Tag &tag) const;
	
	private:
		
		set<string> matrices, samplers, vectors;
		
		Node* createUniform(const Tag &tag) const;
		bool isUniformMatrix(const string &type) const;
		bool isUniformSampler(const string &type) const;
		bool isUniformVector(const string &type) const;
};


#endif

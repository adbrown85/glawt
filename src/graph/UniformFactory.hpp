/*
 * UniformFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef UNIFORMFACTORY_HPP
#define UNIFORMFACTORY_HPP
#include <cstdlib>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include "Factory.hpp"
#include "Uniform.hpp"
#include "UniformInt.hpp"
#include "UniformFloat.hpp"
#include "UniformMatrix.hpp"
#include "UniformSampler.hpp"
#include "UniformVector.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief
 *     Factory for creating different types of Uniform variables.
 */
class UniformFactory : public Factory {
	
	public:
		
		UniformFactory();
		virtual Node* create(const Tag &tag);
		virtual set<string> getClasses();
	
	private:
		
		set<string> matrices, samplers, vectors;
		
		bool isMatrix(const string &type);
		bool isSampler(const string &type);
		bool isVector(const string &type);
};


#endif

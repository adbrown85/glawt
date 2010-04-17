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
#include <sstream>
#include <string>
#include "Uniform.hpp"
#include "UniformInt.hpp"
#include "UniformFloat.hpp"
#include "UniformMatrix.hpp"
#include "UniformSampler.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief
 *     Factory for creating different types of Uniform variables.
 */
class UniformFactory {
	
	public :
		
		static Uniform* create(const Tag &tag);
};


#endif

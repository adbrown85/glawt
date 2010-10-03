/*
 * ShaderFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SHADERFACTORY_HPP
#define SHADERFACTORY_HPP
#include "common.h"
#include "ShaderBuilder.hpp"
using namespace std;


class ShaderFactory {
public:
	static GLuint create(const string &type, const string &filename);
private:
	static map<string,GLuint> shaders;
	static ShaderBuilder builder;
};


#endif

/*
 * ErrorChecker.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef ERRORCHECKER_HPP
#define ERRORCHECKER_HPP
#include "common.h"
#include "Log.hpp"
#include "Exception.hpp"
using namespace std;


/** Utility for checking for OpenGL errors. */
class ErrorChecker {
public:
	static void check(const string &location);
	static void clear();
private:
	static void report(GLenum error, const string &location);
};


#endif

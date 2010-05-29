/*
 * Error.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef ERROR_HPP
#define ERROR_HPP
#include "common.h"
#include "Exception.hpp"
#include "Preprocessor.hpp"
#include "Log.hpp"
using namespace std;


/** @brief Utility for processing error messages.
 * @ingroup system
 */
class Error {
public:
	static void print(GLchar *log,
	                  int handle,
	                  const Preprocessor &preprocessor);
	static void print(GLchar *log,
	                  const map<int,const Preprocessor*> &code);
protected:
	static int findHandle(const string &line);
	static int findLine(const string &line);
	static bool fitsPattern(const string &line);
	static string findMessage(const string &line);
	static void printLine(const string &line,
	                      const map<int,const Preprocessor*> &code);
};


#endif

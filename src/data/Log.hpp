/*
 * Log.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef LOG_HPP
#define LOG_HPP
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <GL/glut.h>
#include "Preprocessor.hpp"
using namespace std;


class Log {
	
	public:
		
		static void print(GLchar *log,
		                  int handle,
		                  const Preprocessor &preprocessor);
		static void print(GLchar *log,
		                  const map<int,const Preprocessor*> &code);
	
	private:
		
		static int findHandle(const string &line);
		static int findLine(const string &line);
		static bool fitsPattern(const string &line);
		static string findMessage(const string &line);
		static void printLine(const string &line,
		                      const map<int,const Preprocessor*> &code);
};


#endif
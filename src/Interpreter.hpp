/*
 * Interpreter.hpp
 *     Interprets directives and issues commands for Gander.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __INTERPRETER_HEADER__
#define __INTERPRETER_HEADER__
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include "Commands.hpp"
using std::map;
using std::string;
using std::cout;
using std::cerr;
using std::endl;



class Interpreter {
	
	
	public :
		
		Interpreter();
		
		void print();
	
	
	private:
		
		map<int, string> com, des;
		
		void initialize();
};


#endif

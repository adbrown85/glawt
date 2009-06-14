/*
 * Interpreter.hpp
 *     Interprets commands and relegates them to delegates.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __GANDER_INTERPRETER_HEADER__
#define __GANDER_INTERPRETER_HEADER__
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include "Command.hpp"
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

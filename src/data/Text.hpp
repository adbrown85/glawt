/*
 * Text.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TEXT_HPP
#define TEXT_HPP
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
using namespace std;


class Text {
	
	public :
		
		static int findFirstNotWordCharacter(const string &text,
		                                     int pos);
		static pair<int,int> findFirstWord(const string &text,
		                                   int pos);
		static int findFirstWordCharacter(const string &text,
		                                  int pos);
		static string replace(const string &text,
		                      map<string,string> &dictionary);
		static string toLower(const string &original);
};


#endif

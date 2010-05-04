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
#include <sstream>
#include <string>
using namespace std;


/**
 * @ingroup data
 * @brief Utility for working with text and strings.
 */
class Text {
public:
	static int count(const string &text,
	                 char character);
	static bool endsWith(const string &text,
	                     char character);
	static int findFirstNotWordCharacter(const string &text,
	                                     int pos=0);
	static pair<int,int> findFirstWord(const string &text,
	                                   int pos=0);
	static int findFirstWordCharacter(const string &text,
	                                  int pos=0);
	static string indent(int times);
	static string replace(const string &text,
	                      map<string,string> &dictionary);
	static string toLower(const string &original);
	static string trim(const string &text,
	                   const string &characters=" ");
};


#endif

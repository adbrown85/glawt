/*
 * Text.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TEXT_HPP
#define TEXT_HPP
#include "common.h"
using namespace std;


/** @brief Utility for working with text and strings.
 * @ingroup system
 */
class Text {
public:
	static int count(const string &text, char character);
	static bool endsWith(const string &text, char character);
	static int findFirstNotWordCharacter(const string &text, int pos=0);
	static pair<int,int> findFirstWord(const string &text, int pos=0);
	static int findFirstWordCharacter(const string &text, int pos=0);
	static string indent(int times);
	static string replace(const string &text, map<string,string> &dictionary);
	static pair<string,string> split(const string &text, char at);
	static string stripLeadingSpaces(const string &text);
	static string stripTrailingSpaces(const string &text);
	static string toLower(string txt);
	static string trim(const string &text, const string &characters=" ");
};


#endif

/*
 * Text.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Text.hpp"


/** @return Number of occurrences of @e character in @e text. */
int Text::count(const string &text, char character) {
	
	int times;
	
	times = 0;
	for (size_t i=0; i<text.length(); ++i) {
		if (text[i] == character) {
			++times;
		}
	}
	return times;
}


/** @return True if @e character is at the last position of @e text. */
bool Text::endsWith(const string &text, char character) {
	
	int last;
	
	last = text.length() - 1;
	return text[last] == character;
}


/** @return Position of first character in text that can be part of a word.
 * 
 * @param text String to search
 * @param pos Position to start from
 */
int Text::findFirstWordCharacter(const string &text, int pos) {
	
	int length;
	
	length = text.length();
	for (int i=pos; i<length; ++i) {
		if (text[i] == '_' || isalpha(text[i])) {
			return i;
		}
	}
	return -1;
}


/** @return Position of first character in text that cannot be part of a word.
 * 
 * @param text String to search
 * @param pos Position to start from
 */
int Text::findFirstNotWordCharacter(const string &text, int pos) {
	
	int length;
	
	length = text.length();
	for (int i=pos; i<length; ++i) {
		if (text[i] != '_' && !isalpha(text[i])) {
			return i;
		}
	}
	return -1;
}


/** @return Start of the first word and its length.
 * 
 * @param text String to search
 * @param pos Position to search from
 */
pair<int,int> Text::findFirstWord(const string &text, int pos) {
	
	int beg, end;
	
	beg = findFirstWordCharacter(text, pos);
	if (beg == -1) {
		return pair<int,int>(-1,0);
	}
	end = findFirstNotWordCharacter(text, beg+1);
	if (end == -1) {
		end = text.length();
	}
	return pair<int,int>(beg,end-beg);
}


/** @return String with @e times * 2 spaces. */
string Text::indent(int times) {
	
	ostringstream stream;
	for (int i=0; i<times; ++i) {
		stream << "  ";
	}
	return stream.str();
}


/** @return Copy of @e text with keys in @e dictionary replaced with values. */
string Text::replace(const string &text, map<string,string> &dictionary) {
	
	map<string,string>::iterator it;
	pair<int,int> bounds;
	string textCopy, value, word;
	
	textCopy = text;
	bounds = Text::findFirstWord(textCopy, 0);
	while (bounds.first != -1) {
		word = textCopy.substr(bounds.first, bounds.second);
		it = dictionary.find(word);
		if (it != dictionary.end()) {
			value = it->second;
			textCopy = textCopy.replace(bounds.first, bounds.second, value);
			bounds = Text::findFirstWord(textCopy, bounds.first+value.length());
		} else {
			bounds = Text::findFirstWord(textCopy, bounds.first+word.length());
		}
	}
	return textCopy;
}


/** @return Pair of strings before and after the first occurence of @e at. */
pair<string,string> Text::split(const string &text, char at) {
	
	size_t pos;
	pair<string,string> couple;
	
	pos = text.find(at);
	couple.first = text.substr(0, pos);
	couple.second = text.substr(pos+1);
	return couple;
}


/** @return Copy of @e text without any spaces at the beginning. */
string Text::stripLeadingSpaces(const string &text) {
	
	size_t pos;
	
	pos = text.find_first_not_of(" \t");
	if (pos > text.length()) {
		return "";
	} else {
		return text.substr(pos);
	}
}


/** @return Copy of @e text without any spaces at the end. */
string Text::stripTrailingSpaces(const string &text) {
	
	int i, last;
	
	last = text.length() - 1;
	for (i=last; i>=0; --i) {
		if (!isspace(text[i])) {
			break;
		}
	}
	return text.substr(0, i+1);
}


/** @return String with each character in @e text converted to lowercase. */
string Text::toLower(string text) {
	
	int length;
	
	// Convert each character
	length = text.length();
	for (int i=0; i<length; ++i)
		text[i] = tolower(text[i]);
	return text;
}


/** @return Copy of @e text with @e characters removed from start and end. */
string Text::trim(const string &text, const string &characters) {
	
	size_t beg, end;
	
	beg = text.find_first_not_of(characters);
	end = text.find_last_not_of(characters);
	return text.substr(beg, end-beg+1);
}


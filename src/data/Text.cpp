/*
 * Text.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Text.hpp"


int Text::count(const string &text,
                char character) {
	
	int times;
	
	times = 0;
	for (size_t i=0; i<text.length(); ++i) {
		if (text[i] == character) {
			++times;
		}
	}
	return times;
}


bool Text::endsWith(const string &text,
                    char character) {
	
	int last;
	
	last = text.length() - 1;
	return text[last] == character;
}


/**
 * @return position of first character in string that can be part of a word.
 * 
 * @param text String to search
 * @param pos Position to start from
 */
int Text::findFirstWordCharacter(const string &text,
                                 int pos) {
	
	int length;
	
	length = text.length();
	for (int i=pos; i<length; ++i) {
		if (text[i] == '_' || isalpha(text[i])) {
			return i;
		}
	}
	return -1;
}


/**
 * @return position of first character in string that cannot be part of a word.
 * 
 * @param text String to search
 * @param pos Position to start from
 */
int Text::findFirstNotWordCharacter(const string &text,
                                    int pos) {
	
	int length;
	
	length = text.length();
	for (int i=pos; i<length; ++i) {
		if (text[i] != '_' && !isalpha(text[i])) {
			return i;
		}
	}
	return -1;
}


/**
 * @return start of the first word and its length.
 * 
 * @param text String to search
 * @param pos Position to search from
 */
pair<int,int> Text::findFirstWord(const string &text,
                                  int pos) {
	
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


string Text::indent(int times) {
	
	ostringstream stream;
	for (int i=0; i<times; ++i) {
		stream << "  ";
	}
	return stream.str();
}


/**
 * Replaces occurences of tokens in a string with their replacements.
 * 
 * @param text String to search
 * @param dictionary Map with tokens and their replacements
 * @return string with the replacements made
 */
string Text::replace(const string &text,
                     map<string,string> &dictionary) {
	
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


/**
 * Converts each character of a string to lowercase.
 * 
 * @param original String to convert.
 */
string Text::toLower(const string &original) {
	
	int length;
	string temp(original);
	
	// Convert each character
	length = temp.length();
	for (int i=0; i<length; ++i)
		temp[i] = tolower(temp[i]);
	return temp;
}


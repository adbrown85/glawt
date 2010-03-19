/*
 * Text.cpp
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
#include "Text.hpp"



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


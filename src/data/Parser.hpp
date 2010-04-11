/*
 * Parser.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PARSER_HPP
#define PARSER_HPP
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "Tag.hpp"
using namespace std;


/**
 * @ingroup data
 * @brief
 *     Reads an XML file, breaking it up into tags and attributes.
 */
class Parser {
	
	public :
		
		bool isComment(string comment);
		string findTagString();
		void open(string filename);
		void parseAttribute(string attributeString, Tag &tag);
		void parseTag(string tagString, Tag &tag);
		void print();
		void skipComment();
		
		vector<Tag> tags;
	
	private :
		
		char buffer[8];
		ifstream file;
};


#endif

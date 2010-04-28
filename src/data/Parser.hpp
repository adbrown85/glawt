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
	
	public:
		
		static Tag create(string text);
		static string findAttribute(stringstream &stream);
		string findTagString();
		bool isComment(string comment);
		void open(string filename);
		static void parseAttribute(string attributeString, Tag &tag);
		void print();
		void skipComment();
		
		vector<Tag> tags;
	
	private:
		
		char buffer[8];
		ifstream file;
};


#endif

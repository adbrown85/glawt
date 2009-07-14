/*
 * Parser.hpp
 *     Parses a scene file.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __PARSER_HPP__
#define __PARSER_HPP__
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "Tag.hpp"
using std::cout;
using std::endl;
using std::ifstream;
using std::ios_base;
using std::map;
using std::string;
using std::stringstream;
using std::vector;



/**
 * @brief
 *     Reads an XML file, breaking it up into tags and attributes.
 * @ingroup backend
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

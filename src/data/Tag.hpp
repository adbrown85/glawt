/*
 * Tag.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TAG_HPP
#define TAG_HPP
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include "Text.hpp"
using namespace std;


/**
 * @ingroup data
 * @brief
 *     XML tag holding a map of attributes and their values.
 */
class Tag {
	
	public:
		
		bool closing, empty;
		map<string,string> attributes;
		string name;
		
		Tag();
		Tag(const string &name);
		void add(const string &key,
		         const string &value);
		void clear();
		bool get(const string &key,
		         bool &value,
		         bool required=true) const;
		bool get(const string &key,
		         char &value,
		         bool required=true) const;
		bool get(const string &key,
		         float &value,
		         bool required=true) const;
		bool get(const string &key,
		         float value[4],
		         bool required=true) const;
		bool get(const string &key,
		         int &value,
		         bool required=true) const;
		bool get(const string &key,
		         string &value,
		         bool required=true,
		         bool lowercase=true) const;
		void setName(const string &name);
		
		friend ostream& operator<<(ostream &stream,
		                           const Tag &tag);
	
	private:
		
		void error(string key) const;
		void error(string key,
		           string type) const;
};

#endif


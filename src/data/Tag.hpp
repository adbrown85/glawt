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
		
		Tag();
		Tag(const string &name);
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
		string getAttribute(const string &name) const;
		string getName() const;
		bool hasAttribute(const string &name) const;
		bool isClosing() const;
		bool isLeaf() const;
		void setAttribute(const string &key,
		                  const string &value);
		void setClosing(bool leaf);
		void setLeaf(bool leaf);
		void setName(const string &name);
		
		friend ostream& operator<<(ostream &stream,
		                           const Tag &tag);
	
	protected:
		
		void error(string key) const;
		void error(string key,
		           string type) const;
	
	private:
		
		bool closing, leaf;
		map<string,string> attributes;
		string name;
};


inline string Tag::getName() const {
	
	return name;
}


inline bool Tag::isClosing() const {
	
	return closing;
}


/**
 * Indicates if the tag was created with a trailing slash.
 */
inline bool Tag::isLeaf() const {
	
	return leaf;
}


inline void Tag::setClosing(bool closing) {
	
	this->closing = closing;
}


inline void Tag::setLeaf(bool leaf) {
	
	this->leaf = leaf;
}


/**
 * Sets the name of the tag.
 */
inline void Tag::setName(const string &name) {
	
	this->name = Text::toLower(name);
}


#endif


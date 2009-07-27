/*
 * Tag.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Tag.hpp"



/**
 * Creates a new, normal tag.
 */
Tag::Tag() {
	
	// Initialze
	clear();
}



/**
 * Resets the tag to an empty state.
 */
void Tag::clear() {
	
	// Reset attributes
	closing = false;
	name = "";
	attributes.clear();
}



/**
 * Throw an exception if the tag doesn't have an attribute.
 * 
 * @param key
 *     Name of the attribute.
 */
void Tag::error(string key) const {
	
	string msg="  Tag named '";
	
	// Build and throw message
	msg += name
	     + "' does not have necessary '"
	     + key
	     + "' attribute!";
	throw msg.c_str();
}



/**
 * Gets the value of an attribute as a character.
 * 
 * @param key
 *     Name of the attribute.
 * @param value
 *     Character to store the value in.
 */
void Tag::get(const string &key,
              char &value,
              bool required) const {
	
	map<string,string>::const_iterator ai;
	
	// Find and convert
	ai = attributes.find(key);
	if (ai != attributes.end())
		value = ai->second[0];
	else if (!required)
		value = '0';
	else
		error(key);
}



/**
 * Gets the value of an attribute as a float.
 * 
 * @param key
 *     Name of the attribute.
 * @param value
 *     Float to store the value in.
 */
void Tag::get(const string &key,
              float &value,
              bool required) const {
	
	map<string,string>::const_iterator ai;
	
	// Find and convert
	ai = attributes.find(key);
	if (ai != attributes.end())
		value = atof(ai->second.c_str());
	else if (!required)
		value = 0.0f;
	else
		error(key);
}



/**
 * Gets the value of an attribute as an integer.
 * 
 * @param key
 *     Name of the attribute.
 * @param value
 *     Integer to store the value in.
 */
void Tag::get(const string &key,
              int &value,
              bool required) const {
	
	map<string,string>::const_iterator ai;
	
	// Find and convert
	ai = attributes.find(key);
	if (ai != attributes.end())
		value = atoi(ai->second.c_str());
	else if (!required)
		value = 0;
	else
		error(key);
}



/**
 * Gets the value of an attribute as a string.
 * 
 * @param key
 *     Name of the attribute.
 * @param value
 *     String to store the value in.
 */
void Tag::get(const string &key,
              string &value,
              bool required) const {
	
	map<string,string>::const_iterator ai;
	
	// Find and convert
	ai = attributes.find(key);
	if (ai != attributes.end())
		value = ai->second;
	else if (!required)
		value = "";
	else
		error(key);
}



ostream& operator<<(ostream &stream,
                    const Tag &tag) {
	
	map<string,string>::const_iterator ai;
	
	// Print name and attributes
	stream << tag.name;
	for (ai=tag.attributes.begin(); ai!=tag.attributes.end(); ++ai)
		stream << " [" 
		       << ai->first << "," 
		       << ai->second 
		       << "]";
	return stream;
}

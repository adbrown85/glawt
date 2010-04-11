/*
 * Tag.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
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
 * Adds an attribute to the tag.
 * 
 * @param key Reference to the name of the attribute.
 * @param value Reference to the value of the attribute.
 */
void Tag::add(const string &key,
              const string &value) {
	
	string keyLower;
	
	keyLower = Text::toLower(key);
	if (keyLower != "file")
		attributes[keyLower] = Text::toLower(value);
	else
		attributes[keyLower] = value;
}


/**
 * Resets the tag to an empty state.
 */
void Tag::clear() {
	
	// Reset attributes
	closing = false;
	empty = false;
	name = "";
	attributes.clear();
}


/**
 * @throws const_char* if the tag doesn't have an attribute.
 * 
 * @param key Name of the attribute.
 */
void Tag::error(string key) const {
	
	ostringstream msg;
	
	// Build and throw message
	msg << "[Tag] Tag named '" << name
	    << "' does not have necessary '" << key
	    << "' attribute.";
	throw msg.str().c_str();
}


/**
 * @throws const_char* if an attribute can't be converted to a type.
 * 
 * @param key Name of the attribute.
 * @param type Type trying to convert to.
 */
void Tag::error(string key,
                string type) const {
	
	ostringstream msg;
	
	// Build and throw message
	msg << "[Tag] In tag named '" << name
	    << "', attribute '" << key
	    << "' cannot be parsed as '" << type
	    << ".";
	throw msg.str().c_str();
}


/**
 * Gets the value of an attribute as a boolean.
 * 
 * @param key Name of the attribute.
 * @param value Boolean to store the value in.
 * @param required If attribute is not found, throw an error.
 */
bool Tag::get(const string &key,
              bool &value,
              bool required) const {
	
	map<string,string>::const_iterator ai;
	
	// Find and convert
	ai = attributes.find(key);
	if (ai != attributes.end()) {
		if (ai->second.compare("true") == 0)
			value = true;
		else if (ai->second.compare("false") == 0)
			value = false;
		else
			error(key, "bool");
		return true;
	}
	else if (!required)
		value = false;
	else
		error(key);
	return false;
}


/**
 * Gets the value of an attribute as a character.
 * 
 * @param key Name of the attribute.
 * @param value Character to store the value in.
 * @param required If attribute is not found, throw an error.
 */
bool Tag::get(const string &key,
              char &value,
              bool required) const {
	
	map<string,string>::const_iterator ai;
	
	// Find and convert
	ai = attributes.find(key);
	if (ai != attributes.end()) {
		value = ai->second[0];
		return true;
	}
	else if (!required)
		value = '0';
	else
		error(key);
	return false;
}


/**
 * Gets the value of an attribute as a float.
 * 
 * @param key Name of the attribute.
 * @param value Float to store the value in.
 * @param required If attribute is not found, throw an error.
 */
bool Tag::get(const string &key,
              float &value,
              bool required) const {
	
	map<string,string>::const_iterator ai;
	
	// Find and convert
	ai = attributes.find(key);
	if (ai != attributes.end()) {
		value = atof(ai->second.c_str());
		return true;
	}
	else if (!required)
		value = 0.0f;
	else
		error(key);
	return false;
}


/**
 * Gets the value of an attribute as an integer.
 * 
 * @param key Name of the attribute.
 * @param value Integer to store the value in.
 * @param required If attribute is not found, throw an error.
 */
bool Tag::get(const string &key,
              int &value,
              bool required) const {
	
	map<string,string>::const_iterator ai;
	
	// Find and convert
	ai = attributes.find(key);
	if (ai != attributes.end()) {
		value = atoi(ai->second.c_str());
		return true;
	}
	else if (!required)
		value = 0;
	else
		error(key);
	return false;
}


/**
 * Gets the value of an attribute as a string.
 * 
 * @param key Name of the attribute.
 * @param value String to store the value in.
 * @param required If attribute is not found, throw an error.
 */
bool Tag::get(const string &key,
              string &value,
              bool required) const {
	
	map<string,string>::const_iterator ai;
	
	// Find and convert
	ai = attributes.find(key);
	if (ai != attributes.end()) {
		value = ai->second;
		return true;
	}
	else if (!required)
		value = "";
	else
		error(key);
	return false;
}


/**
 * Sets the name of this tag.
 */
void Tag::setName(const string &name) {
	
	this->name = Text::toLower(name);
}


/**
 * Prints the %Tag to a stream.
 * 
 * @param stream Stream to print to.
 * @param tag XML tag.
 */
ostream& operator<<(ostream &stream,
                    const Tag &tag) {
	
	map<string,string>::const_iterator ai;
	
	// Print name and attributes
	stream << tag.name;
	if (tag.closing)
		stream << " {closing}";
	if (tag.empty)
		stream << " {empty}";
	for (ai=tag.attributes.begin(); ai!=tag.attributes.end(); ++ai)
		stream << " [" 
		       << ai->first << "," 
		       << ai->second 
		       << "]";
	return stream;
}


/*
 * Tag.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Tag.hpp"


/** Creates an empty tag. */
Tag::Tag() {
	
	clear();
}


/** Creates a tag named @e name. */
Tag::Tag(const string &name) {
	
	clear();
	this->name = name;
}


/** Resets the tag to an empty state. */
void Tag::clear() {
	
	// Reset attributes
	closing = false;
	leaf = false;
	line = 0;
	name = "";
	attributes.clear();
}


/** @throw Exception if tag doesn't have an attribute named @e key. */
void Tag::error(string key) const {
	
	Exception e;
	
	// Build and throw message
	e << getLocation();
	e << "[Tag] Tag named '" << name
	  << "' does not have necessary '" << key
	  << "' attribute.";
	throw e;
}


/** @throw Exception if attribute @e key can't be converted to a @e type. */
void Tag::error(string key, string type) const {
	
	Exception e;
	
	// Build and throw message
	e << getLocation();
	e << "[Tag] In tag named '" << name
	  << "', attribute '" << key
	  << "' cannot be parsed as '" << type
	  << ".";
	throw e;
}


/** Gets the value of an attribute as a boolean. */
bool Tag::get(const string &key, bool &value, bool required) const {
	
	map<string,string>::const_iterator ai;
	string text;
	
	// Find and convert
	ai = attributes.find(key);
	if (ai != attributes.end()) {
		text = Text::toLower(ai->second);
		if (text == "true") {
			value = true;
		} else if (text == "false") {
			value = false;
		} else {
			error(key, "bool");
		}
		return true;
	}
	else if (!required)
		value = false;
	else
		error(key);
	return false;
}


/** Gets the value of an attribute as a character. */
bool Tag::get(const string &key, char &value, bool required) const {
	
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


/** Gets the value of an attribute as a float. */
bool Tag::get(const string &key, float &value, bool required) const {
	
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


/** Gets the value of a four-value float array. */
bool Tag::get(const string &key, float value[4], bool required) const {
	
	map<string,string>::const_iterator ai;
	stringstream stream;
	
	// Find and convert
	ai = attributes.find(key);
	if (ai != attributes.end()) {
		stream << ai->second;
		for (int i=0; i<4; ++i)
			stream >> value[i];
		return true;
	}
	else if (!required) {
		for (int i=0; i<4; ++i)
			value[i] = 0.0f;
	}
	else
		error(key);
	return false;
}


/** Gets the value of an attribute as an integer. */
bool Tag::get(const string &key, int &value, bool required) const {
	
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


bool Tag::get(const string &key, Vector &value, bool required) const {
	
	map<string,string>::const_iterator ai;
	stringstream stream;
	
	// Find and convert
	ai = attributes.find(key);
	if (ai != attributes.end()) {
		stream << ai->second;
		for (int i=0; i<4 && stream; ++i)
			stream >> value[i];
		return true;
	}
	else if (required) {
		error(key);
	}
	return false;
}


/** Gets the value of an attribute as a string.
 * 
 * @param key Name of the attribute.
 * @param value String to store the value in.
 * @param required If attribute is not found, throw an error.
 * @param lowercase True if the value should be converted to lowercase.
 */
bool Tag::get(const string &key,
              string &value,
              bool required,
              bool lowercase) const {
	
	map<string,string>::const_iterator ai;
	
	// Find and convert
	ai = attributes.find(key);
	if (ai != attributes.end()) {
		if (lowercase) {
			value = Text::toLower(ai->second);
		} else {
			value = ai->second;
		}
		return true;
	}
	else if (!required)
		value = "";
	else
		error(key);
	return false;
}


/** @return String describing the location of the tag in the file. */
string Tag::getLocation() const {
	
	return toLocation(filename, line);
}


/** @return String describing the location of a tag in the file. */
string Tag::toLocation(string filename, int line) {
	
	ostringstream stream;
	
	stream << filename << ":" << line << ": ";
	return stream.str();
}


/** @return True if the tag has an attribute named @e name */
bool Tag::hasAttribute(const string &name) const {
	
	map<string,string>::const_iterator it;
	
	it = attributes.find(name);
	return it != attributes.end();
}


/** Gets and sets an attribute in the tag. */
string& Tag::operator[](const string &key) {
	
	return attributes[Text::toLower(key)];
}


/** Gets an attribute in the tag. */
string Tag::operator[](const string &key) const {
	
	map<string,string>::const_iterator it;
	
	it = attributes.find(key);
	if (it != attributes.end()) {
		return it->second;
	} else {
		return "";
	}
}


/** Prints @e tag to @e stream. */
ostream& operator<<(ostream &stream, const Tag &tag) {
	
	map<string,string>::const_iterator ai;
	
	// Print name and attributes
	stream << tag.name;
	stream << " {";
		stream << tag.line;
		if (tag.closing)
			stream << ",closing";
		if (tag.leaf)
			stream << ",leaf";
	stream << "}";
	for (ai=tag.attributes.begin(); ai!=tag.attributes.end(); ++ai) {
		stream << " [" 
		       << ai->first << "," 
		       << ai->second 
		       << "]";
	}
	return stream;
}


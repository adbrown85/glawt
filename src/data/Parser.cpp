/*
 * Parser.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Parser.hpp"


string Parser::findAttribute(stringstream &stream) {
	
	int count=0;
	stringstream buffer;
	string token;
	
	stream >> token;
	while (stream) {
		buffer << token;
		count += Text::count(token, '"') + Text::count(token, '\'');
		if (count >= 2)
			break;
		buffer << ' ';
		stream >> token;
	}
	return buffer.str();
}


/**
 * Finds the next tag in the file.
 * 
 * @return %Tag string without '<' and '>'.
 */
string Parser::findTagString() {
	
	char character;
	string tagString;
	
	// Read until end of tag
	character = file.get();
	while (character != '>') {
		tagString += character;
		character = file.get();
	}
	return tagString;
}


/**
 * Checks if the next few characters indicate a comment.
 * 
 * @param comment Characters that start or end a comment.
 * @return True if the characters indicate a comment.
 */
bool Parser::isComment(string comment) {
	
	int length=comment.length();
	
	// Get next three characters
	for (int i=0; i<length && file; ++i)
		buffer[i] = file.get();
	buffer[length] = '\0';
	file.seekg(-length, ios_base::cur);
	
	// Check if matches comment
	return comment.compare(buffer) == 0;
}


/**
 * Opens a file and starts parsing it.
 * 
 * @param filename Path of the file to open.
 * @throws const_char* if file cannot be opened.
 */
void Parser::open(string filename) {
	
	char character;
	string line, text;
	Tag tag;
	
	// Open file
	file.open(filename.c_str(), ios_base::binary);
	if (!file) {
		ostringstream msg;
		msg << "[Parser] Could not open file '" << filename << "'.";
		throw msg.str().c_str();
	}
	
	// Read and process tags
	character = file.get();
	while (file) {
		if (character == '<') {
			if (isComment("!--"))
				skipComment();
			else {
				text = findTagString();
				tag.clear();
				tag = parseTag(text);
				tags.push_back(tag);
			}
		}
		character = file.get();
	}
}


/**
 * Parses an attribute into a key and value, and then stores it.
 * 
 * @param attribute Attribute as a raw string from the file.
 * @param tag Tag object to store the attribute in.
 */
void Parser::parseAttribute(string attribute,
                            Tag &tag) {
	
	int equalsIndex, length;
	string key, value;
	
	// Find equals sign
	length = attribute.length();
	for (int i=0; i<length; ++i) {
		if (attribute[i] == '=') {
			equalsIndex = i;
			break;
		}
	}
	
	// Store key and value
	key = attribute.substr(0, equalsIndex);
	value = attribute.substr(equalsIndex+2, length-equalsIndex-3);
	tag.add(key, value);
}


/**
 * Parses a tag.
 * 
 * @param tagText Raw text for the tag from the file.
 * @param tag Tag object to store the attributes in.
 */
Tag Parser::parseTag(string text) {
	
	string token;
	stringstream stream;
	Tag tag;
	
	// Remove ending slash and put text in stream
	if (Text::endsWith(text, '/')) {
		text = text.substr(0, text.length()-1);
		tag.empty = true;
	}
	stream.str(text);
	
	// Name
	stream >> token;
	if (token[0] == '/') {
		tag.setName(token.substr(1));
		tag.closing = true;
	} else {
		tag.setName(token);
	}
	
	// Attributes
	token = findAttribute(stream);
	while (stream) {
		parseAttribute(token, tag);
		token = findAttribute(stream);
	}
	
	// Finish
	return tag;
}


/**
 * Prints all the tags in the Parser.
 */
void Parser::print() {
	
	cout << "Tags: " << endl;
	for (size_t i=0; i<tags.size(); ++i)
		cout << "  " << tags[i] << endl;
}


/**
 * Skips a comment.
 */
void Parser::skipComment() {
	
	bool found=false;
	char character;
	
	while (!found) {
		character = file.get();
		if (character == '-' && isComment("->")) {
			for (int i=0; i<2; ++i)
				file.get();
			found = true;
		}
	}
}


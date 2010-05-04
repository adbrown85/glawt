/*
 * Parser.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Parser.hpp"


void Parser::advance() {
	
	character = file.get();
	if (character == '\n') {
		++lineNumber;
	}
}


void Parser::advance(int times) {
	
	for (int i=0; i<times; ++i) {
		advance();
	}
}


/**
 * Creates a tag from text with name and attributes.
 * 
 * @param text Raw text for the tag from the file.
 * @return Tag object to store the attributes in.
 */
Tag Parser::create(string text) {
	
	string key, value;
	stringstream stream;
	Tag tag;
	
	// Remove ending slash
	if (Text::endsWith(text, '/')) {
		text = text.substr(0, text.length()-1);
		tag.setLeaf(true);
	}
	
	// Put text in stream
	stream.str(text);
	
	// Name
	stream >> text;
	if (text[0] == '/') {
		tag.setName(text.substr(1));
		tag.setClosing(true);;
	} else {
		tag.setName(text);
	}
	
	// Attributes
	text = findAttribute(stream);
	while (stream) {
		key = findKeyIn(text);
		value = findValueIn(text);
		tag[key] = value;
		text = findAttribute(stream);
	}
	
	// Finish
	return tag;
}


string Parser::findAttribute(stringstream &stream) {
	
	int count=0;
	ostringstream buffer;
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
 * Parses an attribute into a key and value, and then stores it.
 * 
 * @param attribute Attribute as a raw string from the file.
 * @param tag Tag object to store the attribute in.
 */
void Parser::findKeyValue(const string &attribute,
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
	tag[key] = value;
}


string Parser::findKeyIn(const string &text) {
	
	size_t index;
	
	// Return up to equals sign
	index = text.find('=');
	return Text::trim(text.substr(0, index));
}


string Parser::findValueIn(const string &text) {
	
	size_t index;
	
	// Return after equals sign
	index = text.find('=');
	return Text::trim(text.substr(index+1), " '\"");
}


/**
 * Finds the next tag in the file.
 * 
 * @return %Tag string without '<' and '>'.
 */
string Parser::findTag() {
	
	// Read until end of tag
	buffer.str("");
	advance();
	while (character != '>') {
		buffer << character;
		advance();
	}
	return buffer.str();
}


/**
 * Checks if the next few characters indicate a comment.
 * 
 * @param comment Characters that start or end a comment.
 * @return True if the characters indicate a comment.
 */
bool Parser::match(const string &text) {
	
	// Check if peek matches
	return peek(text.length()) == text;
}


/**
 * Opens a file and starts parsing it.
 * 
 * @param filename Path of the file to open.
 * @throws const_char* if file cannot be opened.
 */
void Parser::open(string filename) {
	
	// Open file
	file.open(filename.c_str(), ios_base::binary);
	if (!file) {
		ostringstream msg;
		msg << "[Parser] Could not open file '" << filename << "'.";
		throw msg.str().c_str();
	}
	lineNumber = 1;
	
	// Parse it
	parse();
}


void Parser::parse() {
	
	Tag tag;
	
	// Read and process tags
	tags.clear();
	skipWhitespace();
	while (file) {
		if (character != '<') {
			throw "[Parser] Tags must start with '<'.";
		} else if (match("<!--")) {
			skip("-->");
		} else {
			tag = create(findTag());
			tag.setLine(lineNumber);
			tags.push_back(tag);
		}
		skipWhitespace();
	}
	file.close();
}


string Parser::peek(int length) {
	
	// Clear the buffer
	buffer.str("");
	
	// Put characters into buffer
	buffer << character;
	for (int i=1; i<length; ++i)
		buffer << (char)file.get();
	
	// Backup and return the string in the buffer
	file.seekg(-(length-1), ios_base::cur);
	return buffer.str();
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
void Parser::skip(const string &text) {
	
	while (!match(text)) {
		advance();
	}
	advance(text.length());
}


void Parser::skipWhitespace() {
	
	advance();
	while (isspace(character))
		advance();
}


/*
 * Parser.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Parser.hpp"


/** Moves the input, checking for new lines as it goes. */
void Parser::advance() {
	
	character = file.get();
	if (character == '\n') {
		++lineNumber;
	}
}


/** Moves the input, checking for new lines as it goes. */
void Parser::advance(int times) {
	
	for (int i=0; i<times; ++i) {
		advance();
	}
}


/** @return Tag created from raw text without '<' and '>'. */
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


/** Finds the next attribute in <i>stream</i> by counting quotes. */
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


/** Parses an attribute into a key and value, and then stores it.
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


/** Returns the key in an attribute key/value pair.
 * 
 * @throw Exception if attribute does not have an equals sign.
 */
string Parser::findKeyIn(const string &text) {
	
	size_t index;
	
	// Return up to equals sign
	index = text.find('=');
	if (index > text.length()) {
		throw Exception("[Parser] Detected attribute without equals sign.");
	}
	return Text::trim(text.substr(0, index));
}


/** Returns the value in an attribute key/value pair.
 * 
 * @throw Exception if there is no text between the quotes.
 */
string Parser::findValueIn(const string &text) {
	
	size_t index;
	
	// Return after equals sign
	index = text.find('=');
	if ((text.length() - index) <= 3) {
		throw Exception("[Parser] Detected empty attribute.");
	}
	return Text::trim(text.substr(index+1), " '\"");
}


/** @return Next tag in the file as text without '<' and '>'. */
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


/** Checks if the current character and the next few matches some text.
 * 
 * @param text String to match against.
 * @return True if everything matches.
 */
bool Parser::match(const string &text) {
	
	// Check if peek matches
	return peek(text.length()) == text;
}


/** Opens a file and starts parsing it.
 * 
 * @param filename Path of the file to open.
 * @throw const_char* if file cannot be opened.
 */
void Parser::open(string filename) {
	
	// Open file
	this->filename = filename;
	file.open(filename.c_str(), ios_base::binary);
	if (!file) {
		Exception e;
		e << "[Parser] Could not open file '" << filename << "'.";
		throw e;
	}
	lineNumber = 1;
	
	// Parse it
	parse();
}


/** Reads XML tags from an input file. */
void Parser::parse() {
	
	Tag tag;
	
	// Read and process tags
	tags.clear();
	skipWhitespace();
	try {
		while (file) {
			if (character != '<') {
				throw Exception("[Parser] Tags must start with '<'.");
			} else if (match("<!--")) {
				skip("-->");
			} else {
				tag = create(findTag());
				tag.setFilename(filename);
				tag.setLine(lineNumber);
				tags.push_back(tag);
			}
			skipWhitespace();
		}
		file.close();
	} catch (Exception e) {
		file.close();
		Exception ex;
		ex << Tag::toLocation(filename, lineNumber) << e;
		throw ex;
	}
}


/** Looks at <i>length</i> characters of input without consuming them. */
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


/** Prints all the tags in the parser. */
void Parser::print() {
	
	cout << "Tags: " << endl;
	for (size_t i=0; i<tags.size(); ++i)
		cout << "  " << tags[i] << endl;
}


/** Skips input until it matches <i>text</i>. */
void Parser::skip(const string &text) {
	
	while (!match(text)) {
		advance();
	}
	advance(text.length());
}


/** Skips spaces, newlines, etc. in the input. */
void Parser::skipWhitespace() {
	
	advance();
	while (isspace(character))
		advance();
}


/*
 * Parser.cpp
 *     Parses a scene file.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Parser.hpp"



/**
 * Checks if the next few characters indicate a comment.
 * 
 * @param comment
 *     Characters that start or end a comment.
 * @return
 *     True if the characters indicate a comment.
 */
bool Parser::isComment(string comment) {
	
	char character;
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
 * @param filename
 *     Path of the file to open.
 */
void Parser::open(string filename) {
	
	char character;
	string line, tagString;
	Tag *tag;
	
	// Open file
	file.open(filename.c_str(), ios_base::binary);
	character = file.get();
	while (file) {
		if (character == '<') {
			if (isComment("!--"))
				skipComment();
			else {
				tagString = findTagString();
				tag = new Tag;
				parseTag(tagString, *tag);
				tags.push_back(*tag);
				delete tag;
			}
		}
		character = file.get();
	}
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



/**
 * Finds the next tag in the file.
 * 
 * @return
 *     %Tag string without '<' and '>'.
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
 * Parses an attribute into a key and value, and then stores it.
 * 
 * @param attributeString
 *     Attribute as a raw string from the file.
 * @param tag
 *     Tag object to store the attribute in.
 */
void Parser::parseAttribute(string attributeString,
                            Tag &tag) {
	
	int equalsIndex, length;
	string key, value;
	
	// Find equals sign
	length = attributeString.length();
	for (int i=0; i<length; ++i) {
		if (attributeString[i] == '=') {
			equalsIndex = i;
			break;
		}
	}
	
	// Store key and value
	key = attributeString.substr(0, equalsIndex);
	value = attributeString.substr(equalsIndex+2, length-equalsIndex-3);
	tag.attributes[key] = value;
}



/**
 * Parses a tag.
 * 
 * @param tagString
 *     Raw text for the tag from the file.
 * @param tag
 *     Tag object to store the attribute in.
 */
void Parser::parseTag(string tagString,
                      Tag &tag) {
	
	char character;
	string token;
	stringstream stream;
	
	// Ignore ending slash (for now)
	if (tagString[tagString.length()-1] == '/')
		tagString = tagString.substr(0, tagString.length()-1);
	stream.str(tagString);
	
	// Name
	stream >> token;
	if (token[0] == '/')
		tag.name = token.substr(1, token.length()-1);
	else
		tag.name = token;
	
	// Attributes
	stream >> token;
	while (stream) {
		parseAttribute(token, tag);
		stream >> token;
	}
}



/**
 * Prints all the tags in the Parser.
 */
void Parser::print() {
	
	for (int i=0; i<tags.size(); ++i)
		cout << tags[i] << endl;
}




/**
 * Simple test program.
 */
int main(int argc, char **argv) {
	
	using namespace std;
	Parser parser;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Parser" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	parser.open("input/scene.xml");
	parser.print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Parser" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

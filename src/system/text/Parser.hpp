/*
 * Parser.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PARSER_HPP
#define PARSER_HPP
#include "common.h"
#include <fstream>
#include <vector>
#include "Exception.hpp"
#include "Tag.hpp"
#include "Text.hpp"
using namespace std;


/** @brief Reads an XML file, breaking it up into tags.
 * 
 * <b>Supports</b>
 *   - Spaces between attribute name, equals, and value
 *   - Spaces in attribute value
 * 
 * <b>Unsupported (or undetermined)</b>
 *   - Spaces between closing slash and &gt; of leaf tag
 *   - Empty attribute values
 *   - Multiple lines in a tag
 * 
 * @ingroup system
 */
class Parser {
public:
	static Tag create(string text);
	int getLineNumber() const;
	vector<Tag> getTags() const;
	void open(string filename);
	void print();
protected:
	void advance();
	void advance(int times);
	static string findAttribute(stringstream &stream);
	static void findKeyValue(const string &text, Tag &tag);
	static string findKeyIn(const string &text);
	static string findValueIn(const string &text);
	string findTag();
	bool match(const string &text);
	void parse();
	string peek(int length);
	void skip(const string &text);
	void skipWhitespace();
private:
	char character;
	ifstream file;
	int lineNumber;
	ostringstream buffer;
	string filename;
	vector<Tag> tags;
};

inline int Parser::getLineNumber() const {return lineNumber;}
inline vector<Tag> Parser::getTags() const {return tags;}


#endif

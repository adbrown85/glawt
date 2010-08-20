/*
 * Code.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Code.hpp"


/** Adds a line to the source code. */
void Code::add(const CodeLine &line) {
	
	lines.push_back(line);
}


/** Adds a line to the source code. */
void Code::add(const string &filename, int number, const string &text) {
	
	CodeLine line;
	
	// Make line
	line.filename = filename;
	line.number = number;
	line.text = text;
	
	// Add it
	lines.push_back(line);
}


/*
 * CodeLoader.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "CodeLoader.hpp"


/** @return True if the line is an include pragma. */
bool CodeLoader::isInclude(const string &line) {
	
	return line.substr(0,8) == "#include";
}


/** Loads a file into the code.
 * 
 * @throws Exception if the file cannot be opened.
 */
void CodeLoader::load(const string &filename) {
	
	bool inComment;
	ifstream file;
	int number;
	string text;
	
	// Open file
	file.open(filename.c_str());
	if (!file) {
		Exception e;
		e << "[CodeLoader] Could not open '" << filename << "'.";
		throw e;
	}
	
	// Load into vector
	number = 0;
	getline(file, text);
	while (file) {
		onLine(filename, ++number, text, inComment);
		getline(file, text);
	}
}


/** Loads an included file if it wasn't already. */
void CodeLoader::onInclude(const string &line) {
	
	string argument, filename;
	set<string>::iterator it;
	
	// Find filename in pragma
	argument = Text::split(line,' ').second;
	filename = Text::trim(argument, "\"\'");
	
	// Check if already loaded
	it = includes.find(filename);
	if (it != includes.end()) {
		return;
	} else {
		includes.insert(filename);
	}
	
	// Make it relative to base file and load it
	filename = Path::getRelativePath(this->filename, filename);
	load(filename);
}


/** Adds a line after filtering it. */
void CodeLoader::onLine(const string &filename,
                        int number,
                        string &text,
                        bool &inComment) {
	
	// Strip comments and trailing space
	text = stripComments(text, inComment);
	text = Text::stripTrailingSpaces(text);
	if (text.empty()) {
		return;
	}
	
	// Check if in comment
	if (inComment)
		return;
	
	// Add line unless an include
	if (isInclude(text)) {
		onInclude(text);
	} else {
		code.add(filename, number, text.append("\n"));
	}
}


/** Loads the file. */
void CodeLoader::parse(const string &filename) {
	
	this->filename = filename;
	code.clear();
	includes.clear();
	load(filename);
}


string CodeLoader::stripComments(const string &line, bool &inComment) {
	
	int length;
	ostringstream buffer;
	
	length = line.length();
	for (int i=0; i<length; ++i) {
		
		// Single-line comment
		if (line[i] == '/' && line[i+1] == '/') {
			break;
		}
		
		// Start of multi-line comment
		if (line[i] == '/' && line[i+1] == '*') {
			inComment = true;
			++i;
			continue;
		}
		
		// End of multi-line comment
		else if (line[i] == '*' && line[i+1] == '/') {
			inComment = false;
			++i;
			continue;
		}
		
		// In comment
		if (inComment) {
			continue;
		}
		
		// Normal
		buffer << line[i];
	}
	return buffer.str();
}


/*
 * Preprocessor.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Preprocessor.hpp"


/**
 * @note Use setFilename() after.
 */
Preprocessor::Preprocessor() {
	
}


Preprocessor::Preprocessor(const string &filename) {
	
	this->filename = filename;
}


void Preprocessor::addBoundary(const string &filename) {
	
	boundaries[lines.size()] = filename;
}


void Preprocessor::addLine(string &line,
                           bool &inComment) {
	
	// Strip comments and trailing space
	line = stripComments(line, inComment);
	line = stripTrailingSpaces(line);
	if (line.empty()) {
		return;
	}
	
	// Pragmas
	if (isPragma(line)) {
		if (!skipLines()) {
			if (isDefine(line)) {
				onDefine(line);
			} else if (isInclude(line)) {
				onInclude(line);
			} else if (isVersion(line)) {
				onVersion(line);
			}
		}
		if (isEndIf(line)) {
			onEndIf(line);
		} else if (isIfNotDefined(line)) {
			onIfNotDefined(line);
		}
	}
	
	// Regular lines
	else if (!skipLines()) {
		line = replaceDefines(line);
		lines.push_back(line);
	}
}


void Preprocessor::addNewLines() {
	
	vector<string>::iterator it;
	
	for (it=lines.begin(); it!=lines.end(); ++it) {
		it->append("\n");
	}
}


string Preprocessor::getFileForLine(int line) const {
	
	map<int,string>::const_iterator it;
	string filename;
	
	for (it=boundaries.begin(); it!=boundaries.end(); ++it) {
		if (it->first > line)
			break;
		filename = it->second;
	}
	return filename;
}


string Preprocessor::getPragmaKey(const string &line) {
	
	return getToken(line, 1);
}


string Preprocessor::getPragmaValue(const string &line) {
	
	return getToken(line, 2);
}


string Preprocessor::getToken(const string &line,
                              int number) {
	
	istringstream buffer(line);
	string token;
	
	for (int i=0; i<=number; ++i) {
		buffer >> token;
	}
	if (!buffer) {
		token = "";
	}
	return token;
}


bool Preprocessor::isDefine(const string &line) {
	
	return line.substr(0,7) == "#define";
}


bool Preprocessor::isEndIf(const string &line) {
	
	return line.substr(0,6) == "#endif";
}


bool Preprocessor::isIfNotDefined(const string &line) {
	
	return line.substr(0,7) == "#ifndef";
}


bool Preprocessor::isInclude(const string &line) {
	
	return line.substr(0,8) == "#include";
}


bool Preprocessor::isPragma(const string &line) {
	
	return line[0] == '#';
}


bool Preprocessor::isVersion(const string &line) {
	
	return line.substr(0,8) == "#version";
}


/**
 * Loads a file into the parser's lines vector.
 * 
 * @throws const_char* if the file cannot be opened.
 */
void Preprocessor::load(const string &filename) {
	
	bool inComment;
	ifstream file;
	string line;
	
	// Open file
	file.open(filename.c_str());
	if (!file) {
		ostringstream message;
		message << "[Preprocessor] Could not open '" << filename << "'.";
		throw message.str().c_str();
	}
	
	// Load into vector
	getline(file, line);
	while (file) {
		addLine(line, inComment);
		getline(file, line);
	}
}


/**
 * @throws const_char* if the token has already been defined
 */
void Preprocessor::onDefine(const string &line) {
	
	map<string,string>::iterator it;
	string key, value;
	
	// Store define
	key = getPragmaKey(line);
	value = getPragmaValue(line);
	it = defines.find(key);
	if (it == defines.end()) {
		defines[key] = value;
	} else {
		ostringstream message;
		message << "[Preprocessor] Token '" << key << "' already defined.";
		throw message.str().c_str();
	}
}


void Preprocessor::onEndIf(const string &line) {
	
	if (!conditionals.empty())
		conditionals.pop();
}


void Preprocessor::onIfNotDefined(const string &line) {
	
	bool result;
	map<string,string>::iterator it;
	string key;
	
	// Test condition and store the result
	key = getPragmaKey(line);
	it = defines.find(key);
	result = (it != defines.end());
	conditionals.push(result);
}


void Preprocessor::onInclude(const string &line) {
	
	string argument, filename;
	
	// Load filename
	argument = getPragmaKey(line);
	filename = stripQuoted(argument);
	filename = FileUtility::getRelativePath(this->filename, filename);
	paths.push(filename);
	addBoundary(filename);
	load(filename);
	paths.pop();
	addBoundary(paths.top());
}


void Preprocessor::onVersion(const string &line) {
	
	lines.push_back(line);
}


void Preprocessor::printBoundaries() {
	
	map<int,string>::iterator it;
	
	for (it=boundaries.begin(); it!=boundaries.end(); ++it) {
		cout << "  [" << it->first 
		     << ", '" << it->second 
		     << "']" << endl;
	}
}


void Preprocessor::printDefines() {
	
	map<string,string>::const_iterator it;
	
	for (it=defines.begin(); it!=defines.end(); ++it) {
		cout << "  [" << it->first << "," << it->second << "]" << endl;
	}
}


void Preprocessor::printLines() {
	
	int width;
	ostringstream stream;
	
	// Find width
	stream << lines.size();
	width = stream.str().length();
	
	// Print
	for (size_t i=0; i<lines.size(); ++i) {
		cout << "  " << setw(width) << i << "  " << lines[i];
	}
}


string Preprocessor::replaceDefines(string &line) {
	
	return Text::replace(line, defines);
}


void Preprocessor::setFilename(const string &filename) {
	
	this->filename = filename;
}


bool Preprocessor::skipLines() {
	
	if (conditionals.empty())
		return false;
	else
		return conditionals.top();
}


void Preprocessor::start() {
	
	paths.push(filename);
	addBoundary(filename);
	load(filename);
	addNewLines();
}


string Preprocessor::stripComments(const string &line,
                                   bool &inComment) {
	
	int length;
	ostringstream buffer;
	
	length = line.length();
	for (int i=0; i<length; ++i) {
		
		// Single-line comment
		if (line[i] == '/' && line[i+1] == '/') {
			break;
		}
		
		// Start of multi-line comment
		else if (line[i] == '/' && line[i+1] == '*') {
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


string Preprocessor::stripFirstToken(const string &line) {
	
	int spacePos;
	
	// Get everything after first space
	spacePos = line.find(' ');
	return line.substr(spacePos+1);
}


string Preprocessor::stripTrailingSpaces(const string &line) {
	
	int i, last;
	
	last = line.length() - 1;
	for (i=last; i>=0; --i) {
		if (!isspace(line[i])) {
			break;
		}
	}
	return line.substr(0, i+1);
}


string Preprocessor::stripQuoted(const string &line) {
	
	string::const_iterator it;
	ostringstream buffer;
	
	// Find first quote
	for (it=line.begin(); it!=line.end(); ++it) {
		if (*it == '\"') {
			++it;
			break;
		}
	}
	
	// No quotes found
	if (it==line.end()) {
		return line;
	}
	
	// Accumulate until next quote
	for (; it!=line.end(); ++it) {
		if (*it == '\"') {
			break;
		}
		buffer << *it;
	}
	return buffer.str();
}


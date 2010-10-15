/*
 * Error.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Error.hpp"


/** @return Line number listed between parentheses. */
int Error::findLine(const string &line) {
	
	int beg, end;
	string token;
	
	beg = line.find('(') + 1;
	end = line.find(')') - 1;
	token = line.substr(beg, end);
	return atoi(token.c_str());
}


/** @return Text after second colon. */
string Error::findMessage(const string &line) {
	
	int beg;
	
	beg = line.find(':') + 1;
	beg = line.find(':', beg) + 1;
	return line.substr(beg);
}


/** @return True if there are two colons in the line. */
bool Error::fitsPattern(const string &line) {
	
	return Text::count(line,':') == 2;
}


void Error::print(GLchar *log, Code &code) {
	
	string line;
	stringstream stream(log);
	
	// Print each line from log
	getline(stream, line);
	while (stream) {
		printLine(line, code);
		getline(stream, line);
	}
}


void Error::printLine(const string &line, Code &code) {
	
	int number;
	ostringstream stream;
	
	// Get line number
	number = findLine(line);
	
	// Check for bad lines
	if (line.empty()) {
		return;
	} else if (!fitsPattern(line) || number == 0) {
		glog << line << endl;
		return;
	}
	
	// Print line substituting file and line number
	glog << code.getLine(number).filename << ":" 
	     << code.getLine(number).number << ":"
	     << findMessage(line)
	     << endl;
}


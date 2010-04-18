/*
 * Log.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Log.hpp"


int Log::findHandle(const string &line) {
	
	return line[0] - 48;
}


int Log::findLine(const string &line) {
	
	int beg, end;
	string token;
	
	beg = line.find('(') + 1;
	end = line.find(')') - 1;
	token = line.substr(beg, end);
	return atoi(token.c_str());
}


string Log::findMessage(const string &line) {
	
	int beg;
	
	beg = line.find(':') + 1;
	beg = line.find(':', beg) + 1;
	return line.substr(beg);
}


bool Log::fitsPattern(const string &line) {
	
	return Text::count(line,':') == 2;
}


void Log::print(GLchar *log,
                int handle,
                const Preprocessor &preprocessor) {
	
	map<int,const Preprocessor*> code;
	
	code[0] = &preprocessor;
	print(log, code);
}


void Log::print(GLchar *log,
                const map<int,const Preprocessor*> &code) {
	
	string line;
	stringstream stream(log);
	
	// Print each line from log
	getline(stream, line);
	while (stream) {
		printLine(line, code);
		getline(stream, line);
	}
}


void Log::printLine(const string &line,
                    const map<int,const Preprocessor*> &code) {
	
	int handle, lineNum;
	ostringstream stream;
	const Preprocessor *preprocessor;
	map<int,const Preprocessor*>::const_iterator it;
	
	// Get line number
	lineNum = findLine(line);
	
	// Check for bad lines
	if (line.empty())
		return;
	if (!fitsPattern(line) || lineNum == 0) {
		cerr << line << endl;
		return;
	}
	
	// Find preprocessor
	handle = findHandle(line);
	it = code.find(0);
	if (it == code.end())
		throw "[Log] Could not find code of handle.";
	preprocessor = it->second;
	
	// Print line substituting file and line number
	cerr << preprocessor->getFileForLine(lineNum) << "(" 
	     << preprocessor->getRealLineNumber(lineNum) << "):"
	     << findMessage(line)
	     << endl;
}


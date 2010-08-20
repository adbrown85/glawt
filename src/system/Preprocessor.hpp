/*
 * Preprocessor.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CODELOADER_HPP
#define CODELOADER_HPP
#include "common.h"
#include <fstream>
#include <iomanip>
#include "Exception.hpp"
#include "Path.hpp"
#include "Text.hpp"
#include "Code.hpp"
using namespace std;


/** @brief Utility for preprocessing C-like code.
 * 
 * Basically, %Preprocessor simply looks through C-like code and performs a few 
 * simple operations.  First, if it finds an @e include directive, it replaces 
 * that line with the lines from the appropriate file.  Lastly, it strips both 
 * multiline and single line comments, as well as trailing spaces.
 * 
 * @ingroup system
 */
class Preprocessor {
public:
	void parse(const string &filename);
public:    // Accessors
	Code getCode() const;
protected: // Helpers
	bool isInclude(const string &line);
	void load(const string &filename);
	void onInclude(const string &line);
	void onLine(const string &file, int number, string &text, bool &inComment);
	string stripComments(const string &line, bool &inComment);
private:
	set<string> includes;
	string filename;
	Code code;
};

/** @return the lines of the file that are actual code. */
inline Code Preprocessor::getCode() const {return code;}


#endif

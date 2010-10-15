/*
 * Path.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PATH_HPP
#define PATH_HPP
#include "common.h"
#include <cctype>
#include <cstring>
#include <vector>
#include "Exception.hpp"
using namespace std;


/** @brief Utility for working with filenames and file paths.
 * @ingroup system
 */
class Path {
public:
	static string build(const string &root,
	                    vector<string> &parts);
	static string expand(const string &path);
	static string getBasename(const string &path);
	static string getDirname(const string &path);
	static string getExtension(const string &path);
	static string getInternals(const string &path);
	static string getRelativePath(const string &base,
	                              const string &filename);
	static string getRoot(const string &path);
	static bool hasWindowsRoot(const string& token);
	static bool isAbsolutePath(const string& filename);
	static bool isSeparator(char character);
	static bool isWindowsRoot(const string& token);
	static string mergePaths(const string &root,
	                         vector<string> &base,
	                         vector<string> &change);
	static string stripRoot(const string &path);
	static void tokenize(const string &filename,
	                     vector<string> &tokens);
};


#endif


/*
 * FileUtility.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef FILEUTILITY_HPP
#define FILEUTILITY_HPP
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;


/**
 * @ingroup data
 * @brief
 *     Utility for working with file paths.
 */
class FileUtility {
public:
	
	static string build(const string &root,
	                    vector<string> &parts);
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
	static string replaceEnvironmentVariable(const string &path);
	static string stripRoot(const string &path);
	static void tokenize(const string &filename,
	                     vector<string> &tokens);
};


#endif


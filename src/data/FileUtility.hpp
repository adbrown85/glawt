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
#include <string>
#include <vector>
using namespace std;



class FileUtility {
	
	
	public:
		
		static string getRelativePath(const string &base,
		                              const string &filename);
		static bool isAbsolutePath(const string& filename);
	
	
	private:
		
		static void build(string &result,
		                  vector<string> &parts);
		static void tokenize(const string &filename,
		                     vector<string> &tokens,
		                     string *root);
};


#endif


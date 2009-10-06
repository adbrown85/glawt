/*
 * FileUtility.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "FileUtility.hpp"



void FileUtility::build(string &result,
                        vector<string> &parts) {
	
	vector<string>::iterator it;
	
	// Build up parts
	for (it=parts.begin(); it!=parts.end()-1; ++it) {
		if (*it != ".." && *it != ".") {
			result += *it;
			result += '/';
		}
	}
	result += *it;
}



/**
 * Makes a filename relative to another path.
 * 
 * @param primary
 *     Path used as the base.
 * @param filename
 *     Path to make relative to base.
 */
string FileUtility::getRelativePath(const string &primary,
                                    const string &secondary) {
	
	string root, result;
	vector<string> stack, list;
	vector<string>::iterator it;
	
	// Check for empty strings
	if (primary.empty() || secondary.empty())
		throw "[Gander,FileUtility] Cannot use an empty string.";
	
	// Check for absolute path
	if (isAbsolutePath(secondary))
		return secondary;
	
	// Fill vectors
	tokenize(primary, stack, &root);
	tokenize(secondary, list, NULL);
	stack.pop_back();
	
	// Check for special case of primary path in root
	if (isAbsolutePath(primary) && stack.empty()) {
		result = root;
		build(result, list);
		return result;
	}
	
	// Manipulate stack according to list
	for (it=list.begin(); it!=list.end(); ++it) {
		if (*it == ".")
			continue;
		else if (*it == "..")
			stack.pop_back();
		else {
			stack.push_back(*it);
		}
	}
	
	// Build string from stack
	build(result, stack);
	return result;
}



/**
 * Checks if a filename is an absolute path.
 * 
 * @return
 *     True if the filename is an absolute path.
 */
bool FileUtility::isAbsolutePath(const string& filename) {
	
	// Check for Unix absolute path
	if (filename[0] == '/')
		return true;
	
	// Check for Windows absolute path
	if (filename.length() < 3)
		return false;
	if (isalpha(filename[0])
	    && filename[1] == ':'
	    && (filename[2] == '/' || filename[2] == '\\'))
		return true;
	return false;
}



/**
 * Splits a filename up into tokens.
 * 
 * @param filename
 *     Path to split up.
 * @param tokens
 *     Parts of the path.
 */
void FileUtility::tokenize(const string &filename,
                           vector<string> &tokens,
                           string *root) {
	
	bool skipSeparator;
	string token;
	
	// Skip first separator for absolute paths
	skipSeparator = isAbsolutePath(filename);
	
	// Split up by slashes
	for (int i=0; i<filename.length(); ++i) {
		if (filename[i] == '/' || filename[i] == '\\') {
			if (!skipSeparator) {
				tokens.push_back(token);
				token.clear();
				continue;
			}
			if (root != NULL)
				*root = token + filename[i];
			skipSeparator = false;
		}
		token += filename[i];
	}
	tokens.push_back(token);
}


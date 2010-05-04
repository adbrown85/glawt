/*
 * FileUtility.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "FileUtility.hpp"
#include <cassert>


void print(const string &result) {
	
	if (result.empty()) {
		cout << "  {empty}" << endl;
	} else {
		cout << "  " << result << endl;
	}
}


void testExtension(const string &path,
                   const string &answer) {
	
	string result;
	
	print(path);
	result = FileUtility::getExtension(path);
	print(result);
	assert(result == answer);
}


void testEnvironmentVariable(const string &path) {
	
	string result;
	
	result = FileUtility::replaceEnvironmentVariable(path);
	print(result);
}


/**
 * Tests relative path function.
 */
void testRelativePath(const string &A,
                      const string &B,
                      const string &answer) {
	
	string result;
	
	// Get result and print
	cout << "Testing relative path..." << endl;
	cout << "  A: " << A << endl;
	cout << "  B: " << B << endl;
	result = FileUtility::getRelativePath(A, B);
	print(result);
	assert(result == answer);
}


/**
 * Unit test for %FileUtility.
 */
int main() {
	
	vector<string> tokens;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "FileUtility" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Basename
	cout << "\nTesting getBasename" << endl;
	print(FileUtility::getBasename("input/scene.xml"));
	
	// Dirname
	cout << "\nTesting getDirname" << endl;
	print(FileUtility::getDirname("../../scene.xml"));
	print(FileUtility::getDirname("input/scene.xml"));
	print(FileUtility::getDirname("scene.xml"));
	print(FileUtility::getDirname("/scene.xml"));
	
	// Environment variables
	cout << "\nTesting environment variable" << endl;
	testEnvironmentVariable("${GANDER}/glsl/outline.glsl");
	testEnvironmentVariable("/usr/local/gander/glsl/outline.glsl");
	
	// Extension
	cout << "\nTesting extension" << endl;
	testExtension("scene.xml", "xml");
	
	// Internals
	cout << "\nTesting getInternals" << endl;
	print(FileUtility::getInternals("input/scene.xml"));
	print(FileUtility::getInternals("/input/scene.xml"));
	print(FileUtility::getInternals("./input/scene.xml"));
	print(FileUtility::getInternals("../../input/scene.xml"));
	print(FileUtility::getInternals("scene.xml"));
	print(FileUtility::getInternals("gander/input/scene.xml"));
	print(FileUtility::getInternals("C:\\scene.xml"));
	print(FileUtility::getInternals("C:\\gander/input/scene.xml"));
	
	// Tokenize
	cout << "\nTesting tokenize" << endl;
	FileUtility::tokenize("input/scene.xml", tokens);
	for (size_t i=0; i<tokens.size(); ++i) {
		print(tokens[i]);
	}
	
	// Test both relative
	cout << "\nWhen both A and B are relative..." << endl;
	testRelativePath("input\\scene.xml",
	                 "glsl/file.frag",
	                 "input/glsl/file.frag");
	testRelativePath("input/scene.xml",
	                 "../glsl/file.frag",
	                 "glsl/file.frag");
	testRelativePath("input/scene.xml",
	                 "../../../glsl/file.frag",
	                 "../../glsl/file.frag");
	testRelativePath("../../input/basic.vert",
	                 "file.frag",
	                 "../../input/file.frag");
	
	// Test if any are absolute paths
	cout << "\nWhen A or B is absolute..." << endl;
	testRelativePath("input/scene.xml",
	                 "/home/user/gander/glsl/file.frag",
	                 "/home/user/gander/glsl/file.frag");
	testRelativePath("/home/user/gander/input/scene.xml",
	                 "glsl/file.frag",
	                 "/home/user/gander/input/glsl/file.frag");
	testRelativePath("/home/user/gander/input/scene.xml",
	                 "../glsl/file.frag",
	                 "/home/user/gander/glsl/file.frag");
	
	// Test if A has no directory
	cout << "\nWhen A has no directory..." << endl;
	testRelativePath("scene.xml",
	                 "../../glsl/file.frag",
	                 "../../glsl/file.frag");
	
	// Test if A is in root
	cout << "\nWhen A is in root..." << endl;
	try {
		testRelativePath("/scene.xml",
		                 "../glsl/file.frag",
		                 "/glsl/file.frag");
		assert(false);
	} catch (Exception &e) {
		cerr << e << endl;
	}
	try {
		testRelativePath("C:\\scene.xml",
		                 "../glsl/file.frag",
		                 "C:\\glsl/file.frag");
		assert(false);
	} catch (Exception &e) {
		cerr << e << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "FileUtility" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}


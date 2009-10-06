/*
 * FileUtility.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "FileUtility.hpp"
#include <cassert>



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
	cout << "  " << result << endl;
	assert(result == answer);
}



/**
 * Unit test for %FileUtility.
 */
int main() {
	
	string A, B;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "FileUtility" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test both relative
	cout << "When both A and B are relative..." << endl;
	testRelativePath("input\\scene.xml",
	                 "glsl/file.frag",
	                 "input/glsl/file.frag");
	testRelativePath("input/scene.xml",
	                 "../glsl/file.frag",
	                 "glsl/file.frag");
	testRelativePath("input/scene.xml",
	                 "../../../glsl/file.frag",
	                 "../../glsl/file.frag");
	
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
	
	// Test if A is in root
	cout << "\nWhen A is in root..." << endl;
	testRelativePath("/scene.xml",
	                 "../glsl/file.frag",
	                 "/glsl/file.frag");
	testRelativePath("C:\\scene.xml",
	                 "../glsl/file.frag",
	                 "C:\\glsl/file.frag");
	
	// Test if A has no directory
	cout << "\nWhen A has no directory..." << endl;
	testRelativePath("scene.xml",
	                 "../../glsl/file.frag",
	                 "../../glsl/file.frag");
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "FileUtility" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}


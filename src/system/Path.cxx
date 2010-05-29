/*
 * Path.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Path.hpp"
#include <cassert>


/* Unit test for Path. */
class PathTest {
public:
	void testBasename();
	void testDirname();
	void testExtension();
	void testExpand();
	void testInternals();
	void testRelativePath();
	void testTokenize();
protected:
	void print(string result);
	void testExpandWith(string);
	void testExtensionWith(string path, string answer);
	void testRelativePathWith(string A, string B, string answer);
};


void PathTest::print(string result) {
	
	if (result.empty()) {
		cout << "  {empty}" << endl;
	} else {
		cout << "  " << result << endl;
	}
}


void PathTest::testBasename() {
	
	cout << "\nTesting getBasename" << endl;
	print(Path::getBasename("input/scene.xml"));
}


void PathTest::testDirname() {
	
	cout << "\nTesting getDirname" << endl;
	print(Path::getDirname("../../scene.xml"));
	print(Path::getDirname("input/scene.xml"));
	print(Path::getDirname("scene.xml"));
	print(Path::getDirname("/scene.xml"));
}


void PathTest::testExtension() {
	
	cout << "\nTesting extension" << endl;
	testExtensionWith("scene.xml", "xml");
}


void PathTest::testExtensionWith(string path, string answer) {
	
	string result;
	
	print(path);
	result = Path::getExtension(path);
	print(result);
	assert(result == answer);
}


void PathTest::testExpand() {
	
	cout << "\nTesting expand" << endl;
	testExpandWith("${GANDER}/glsl/outline.glsl");
	testExpandWith("/usr/local/gander/glsl/outline.glsl");
}


void PathTest::testExpandWith(string path) {
	
	string result;
	
	result = Path::expand(path);
	print(result);
}


void PathTest::testInternals() {
	
	cout << "\nTesting getInternals" << endl;
	print(Path::getInternals("input/scene.xml"));
	print(Path::getInternals("/input/scene.xml"));
	print(Path::getInternals("./input/scene.xml"));
	print(Path::getInternals("../../input/scene.xml"));
	print(Path::getInternals("scene.xml"));
	print(Path::getInternals("gander/input/scene.xml"));
	print(Path::getInternals("C:\\scene.xml"));
	print(Path::getInternals("C:\\gander/input/scene.xml"));
}


void PathTest::testRelativePath() {
	
	// Test both relative
	cout << "\nWhen both A and B are relative..." << endl;
	testRelativePathWith("input\\scene.xml",
	                     "glsl/file.frag",
	                     "input/glsl/file.frag");
	testRelativePathWith("input/scene.xml",
	                     "../glsl/file.frag",
	                     "glsl/file.frag");
	testRelativePathWith("input/scene.xml",
	                     "../../../glsl/file.frag",
	                     "../../glsl/file.frag");
	testRelativePathWith("../../input/basic.vert",
	                     "file.frag",
	                     "../../input/file.frag");
	
	// Test if any are absolute paths
	cout << "\nWhen A or B is absolute..." << endl;
	testRelativePathWith("input/scene.xml",
	                     "/home/user/gander/glsl/file.frag",
	                     "/home/user/gander/glsl/file.frag");
	testRelativePathWith("/home/user/gander/input/scene.xml",
	                     "glsl/file.frag",
	                     "/home/user/gander/input/glsl/file.frag");
	testRelativePathWith("/home/user/gander/input/scene.xml",
	                     "../glsl/file.frag",
	                     "/home/user/gander/glsl/file.frag");
	
	// Test if A has no directory
	cout << "\nWhen A has no directory..." << endl;
	testRelativePathWith("scene.xml",
	                     "../../glsl/file.frag",
	                     "../../glsl/file.frag");
	
	// Test if A is in root
	cout << "\nWhen A is in root..." << endl;
	try {
		testRelativePathWith("/scene.xml",
		                     "../glsl/file.frag",
		                     "/glsl/file.frag");
		assert(false);
	} catch (Exception &e) {
		cerr << e << endl;
	}
	try {
		testRelativePathWith("C:\\scene.xml",
		                     "../glsl/file.frag",
		                     "C:\\glsl/file.frag");
		assert(false);
	} catch (Exception &e) {
		cerr << e << endl;
	}
}


void PathTest::testRelativePathWith(string A, string B, string answer) {
	
	string result;
	
	// Get result and print
	cout << "Testing relative path..." << endl;
	cout << "  A: " << A << endl;
	cout << "  B: " << B << endl;
	result = Path::getRelativePath(A, B);
	print(result);
	assert(result == answer);
}


void PathTest::testTokenize() {
	
	vector<string> tokens;
	
	cout << "\nTesting tokenize" << endl;
	Path::tokenize("input/scene.xml", tokens);
	for (size_t i=0; i<tokens.size(); ++i) {
		print(tokens[i]);
	}
}


/* Run test. */
int main() {
	
	PathTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Path" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	test.testBasename();
	test.testDirname();
	test.testExtension();
	test.testInternals();
	test.testTokenize();
	test.testRelativePath();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Path" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}


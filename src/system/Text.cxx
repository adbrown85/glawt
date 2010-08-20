/*
 * Text.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Text.hpp"
#include <cassert>


class TextTest {
public:
	void setUp();
	void testCount();
	void testFirstWord();
	void testFirstWordCharacter();
	void testFirstNotWordCharacter();
	void testReplacements();
	void testTrim();
	void testStripLeadingSpaces();
	void testStripTrailingSpaces();
	void testSplit();
protected:
	void testFirstWordWith(const string &text, int first, int length);
};


void TextTest::setUp() {
	
	cout << "Setting up..." << endl;
}


void TextTest::testCount() {
	
	int result;
	
	cout << "\nTesting count..." << endl;
	result = Text::count("abracadabra", 'a');
	cout << "  " << result << endl;
	assert(result == 5);
}


void TextTest::testFirstWordCharacter() {
	
	int pos;
	string text;
	
	cout << "\nTesting first word character" << endl;
	text = "    (foo)";
	pos = Text::findFirstWordCharacter(text, 0);
	cout << "  " << pos << endl;
	assert(pos == 5);
}


void TextTest::testFirstNotWordCharacter() {
	
	int pos;
	string text;
	
	cout << "\nNext first not word character" << endl;
	text = "    (foo)";
	pos = Text::findFirstNotWordCharacter(text, pos+1);
	cout << "  " << pos << endl;
	assert(pos == 8);
}


void TextTest::testFirstWord() {
	
	cout << "\nFirst word" << endl;
	testFirstWordWith("    (foo)", 5, 3);
	testFirstWordWith(" 78 * 45", -1, 0);
	testFirstWordWith(" 123foobar", 4, 6);
}


void TextTest::testFirstWordWith(const string &text, int first, int length) {
	
	pair<int,int> bounds;
	
	bounds = Text::findFirstWord(text, 0);
	cout << "  " << bounds.first << " " << bounds.second << endl;
	assert(bounds.first  == first );
	assert(bounds.second == length);
	if (bounds.second != 0) {
		cout << "  " << text.substr(bounds.first,bounds.second) << endl;
	}
}


void TextTest::testReplacements() {
	
	map<string,string> dictionary;
	string result;
	
	cout << "\nReplacements" << endl;
	dictionary["PI_CONSTANT"] = "3.14";
	dictionary["E_CONSTANT"] = "2.72";
	result = Text::replace("4*PI_CONSTANT + E_CONSTANT BLAH", dictionary);
	cout << "  " << result << endl;
	assert(result == "4*3.14 + 2.72 BLAH");
}


void TextTest::testTrim() {
	
	string result;
	
	cout << "\nTrim" << endl;
	result = Text::trim("  blah blah blah  ");
	cout << "  '" << result << "'" << endl;
	assert(result == "blah blah blah");
	result = Text::trim("  \"blah blah blah\"  ", "'\" ");
	cout << "  '" << result << "'" << endl;
	assert(result == "blah blah blah");
}


void TextTest::testSplit() {
	
	pair<string,string> result;
	
	cout << "\nSplit" << endl;
	result = Text::split("spot.ambient", '.');
	cout << "  " << result.first << endl;
	cout << "  " << result.second << endl;
	assert(result.first == "spot");
	assert(result.second == "ambient");
}


void TextTest::testStripLeadingSpaces() {
	
	string result;
	
	cout << "\nStrip Leading Spaces" << endl;
	result = Text::stripLeadingSpaces("\t // This is a comment");
	cout << "  " << result << endl;
	assert(result == "// This is a comment");
}


void TextTest::testStripTrailingSpaces() {
	
	string result;
	
	cout << "\nStrip Trailing Spaces" << endl;
	result = Text::stripTrailingSpaces("// This is a comment    ");
	cout << "  " << result << endl;
	assert(result == "// This is a comment");
}



int main(int argc, char *argv[]) {
	
	int pos, result;
	pair<int,int> bounds;
	string text;
	
	TextTest test;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Text" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	test.setUp();
	test.testCount();
	test.testFirstWordCharacter();
	test.testFirstNotWordCharacter();
	test.testFirstWord();
	test.testReplacements();
	test.testTrim();
	test.testSplit();
	test.testStripLeadingSpaces();
	test.testStripTrailingSpaces();
	
	// End
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Text" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}


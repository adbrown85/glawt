/*
 * Text.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Text.hpp"
#include <cassert>


int main(int argc,
         char *argv[]) {
	
	int pos;
	map<string,string> dictionary;
	pair<int,int> bounds;
	string text;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Text" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// First word character
	cout << "First word character" << endl;
	text = "    (foo)";
	pos = Text::findFirstWordCharacter(text, 0);
	cout << "  " << pos << endl;
	assert(pos == 5);
	
	// Next first not word character
	cout << "\nNext first not word character" << endl;
	text = "    (foo)";
	pos = Text::findFirstNotWordCharacter(text, pos+1);
	cout << "  " << pos << endl;
	assert(pos == 8);
	
	// First word
	cout << "\nFirst word" << endl;
	text = "    (foo)";
	bounds = Text::findFirstWord(text, 0);
	cout << "  " << bounds.first << " " << bounds.second << endl;
	cout << "  " << text.substr(bounds.first,bounds.second) << endl;
	assert(bounds.first == 5);
	assert(bounds.second == 3);
	
	// First word with none
	cout << "\nFirst word with none" << endl;
	bounds = Text::findFirstWord(" 78 * 45", 0);
	cout << "  " << bounds.first << " " << bounds.second << endl;
	assert(bounds.first == -1);
	assert(bounds.second == 0);
	
	// First word with nothing after it
	cout << "\nFirst word with nothing after it" << endl;
	bounds = Text::findFirstWord(" 123foobar", 0);
	cout << "  " << bounds.first << " " << bounds.second << endl;
	assert(bounds.first == 4);
	assert(bounds.second == 6);
	
	// Replacements
	cout << "\nReplacements" << endl;
	dictionary["SOME_CONSTANT"] = "3.14";
	dictionary["ALSO_CONSTANT"] = "1.76";
	text = Text::replace("4*SOME_CONSTANT + ALSO_CONSTANT BLAH", dictionary);
	cout << text;
	
	// End
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Text" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}


/*
 * Parser.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <iostream>
#include "Parser.hpp"
using namespace std;



/**
 * Simple test program.
 */
int main(int argc, char **argv) {
	
	Parser parser;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Parser" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	parser.open("Parser.xml");
	parser.print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Parser" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

/*
 * Sequence.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;



class Sequence {
	
	
	public :
		
		Sequence(string directory);
		void printFilenames() const;
		
		string getFilename(int number) const {return filenames[number-1];}
		int getSize() const {return filenames.size();}
	
	
	private:
		
		string directory, basename;
		vector<string> filenames;
		
		void initBasename();
		void initFilenames();
		void verifyDirectory();
		void verifyFilenames();
};


#endif

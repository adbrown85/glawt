/*
 * Slice.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef SLICE_HPP
#define SLICE_HPP
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "Sequence.hpp"
typedef unsigned char byte;



class Slice {
	
	
	public :
		
		Slice(Sequence *sequence,
		      int width,
		      int number);
		~Slice();
		void printData();
		unsigned short readShort(ifstream &file);
		
		unsigned short* getData() {return data;}
		int getWidth() {return width;}
	
	
	private:
		
		unsigned short *data;
		int number, size, width;
		Sequence *sequence;
		
		Slice();
		void load();
};


#endif

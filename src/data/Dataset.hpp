/*
 * Dataset.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef DATASET_HPP
#define DATASET_HPP
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;



class Dataset {
	
	
	public :
		
		Dataset(const string &filename);
		~Dataset();
		void print() const;
		
		int getDepth() const {return size[2];}
		int getHeight() const {return size[1];}
		int getWidth() const {return size[0];}
	
	
	private:
		
		short *data;
		int dataOffset, headerOffset, length;
		int max, min, pitch[3], range[2], size[3];
		string endian, filename, type;
		
		Dataset();
		void checkHeader();
		void initData();
		void readData();
		void readHeader();
};


#endif

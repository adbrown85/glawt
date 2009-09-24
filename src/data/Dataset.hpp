/*
 * Dataset.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef DATASET_HPP
#define DATASET_HPP
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <GL/glut.h>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <utility>
#include "DatasetHeader.hpp"
#include "Index.hpp"
using namespace std;



/**
 * @brief
 *     Loads and holds volumetric data.
 * @ingroup data
 */
class Dataset {
	
	
	public :
		
		Dataset(string filename);
		Dataset(const Dataset &original);
		virtual ~Dataset();
		void print() const {header.print();}
		void print(Index I);
		
		void get(const Index &I,
		         void *&value,
		         GLenum &type) const;
		int getBlock() const {return block;}
		void* getData() const {return data;}
		int getDepth() const {return depth;}
		int getHeight() const {return height;}
		GLenum getType() const {return type;}
		int getWidth() const {return width;}
		void set(const Index &I,
		         const void *value,
		         GLenum type);
	
	
	private:
		
		DatasetHeader header;
		GLenum type;
		int block, length;
		int width, height, depth, widthTimesHeight;
		void *data;
		
		char* findPosition(const Index &I) const;
		void initDimensions();
		void initTypeBlock();
		void readData();
		void checkIndex(const Index &I) const;
};


#endif

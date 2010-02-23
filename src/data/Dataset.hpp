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
#include "Tag.hpp"
using namespace std;



/**
 * @brief
 *     Loads and holds volumetric data.
 * @ingroup data
 */
class Dataset {
	
	
	public :
		
		Dataset(string filename);
		Dataset(const Tag &tag);
		virtual ~Dataset();
		virtual void print() const {header.print();}
		virtual void print(Index I);
		
		virtual void get(const Index &I,
		                 void *&value) const;
		virtual void get(const Index &I,
		                 void *&value,
		                 GLenum &type) const;
		virtual unsigned char getAsByte(const Index &I) const;
		virtual float getAsFloat(const Index &I) const;
		virtual short getAsShort(const Index &I) const;
		virtual int getBlock() const {return block;}
		virtual void* getData() const {return data;}
		virtual int getDepth() const {return depth;}
		virtual int getHeight() const {return height;}
		virtual int getMaximumDimension() const;
		virtual GLenum getType() const {return type;}
		virtual int getWidth() const {return width;}
		virtual void set(const Index &I,
		                 const void *value,
		                 GLenum type);
	
	
	private:
		
		DatasetHeader header;
		GLenum type;
		int block, length;
		int width, height, depth, widthTimesHeight;
		void *data;
		
		virtual char* findPosition(const Index &I) const;
		virtual void init();
		virtual void initDimensions();
		virtual void initTypeBlock();
		virtual void readData();
		virtual void checkIndex(const Index &I) const;
};


#endif

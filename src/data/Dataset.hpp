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
	
	
	public:
		
		Dataset(string filename);
		Dataset(const Tag &tag);
		virtual ~Dataset();
		virtual void print() const;
		virtual void print(Index I);
		
		virtual void get(const Index &I,
		                 void *&value) const;
		virtual void get(const Index &I,
		                 void *&value,
		                 GLenum &type) const;
		virtual unsigned char getAsByte(const Index &I) const;
		virtual float getAsFloat(const Index &I) const;
		virtual short getAsShort(const Index &I) const;
		virtual int getBlock() const;
		virtual void* getData();
		virtual int getDepth() const;
		virtual int getHeight() const;
		virtual int getMaximumDimension() const;
		virtual GLenum getType() const;
		virtual int getWidth() const;
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


/**
 * @return Number of bytes in one sample.
 */
inline int Dataset::getBlock() const {return block;}


/**
 * @return Pointer to the start of all the data.
 */
inline void* Dataset::getData() {return data;}


/**
 * @return Number of samples in the Z direction.
 */
inline int Dataset::getDepth() const {return depth;}


/**
 * @return Number of samples in the Y direction.
 */
inline int Dataset::getHeight() const {return height;}


/**
 * Currently, the return value will be one of 
 * 
 * @li @c GL_UNSIGNED_BYTE,
 * @li @c GL_SHORT, or 
 * @li @c GL_FLOAT,
 * 
 * which can then be used in a @c switch statement.
 * 
 * @return Enumeration representing the type of the data.
 */
inline GLenum Dataset::getType() const {return type;}


/**
 * @return Number of samples in the X direction.
 */
inline int Dataset::getWidth() const {return width;}


/**
 * Prints the header of the dataset.
 */
inline void Dataset::print() const {header.print();}



#endif
